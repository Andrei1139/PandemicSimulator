#include "simulator.hpp"

void Simulator::display_statuses() const {
    for (auto& person: population.persons) {
        std::cout << person.status_string() << '\n';
    }
}

Simulator::Symbol Simulator::get_person_symbol(const Person& person) const {
    if (person.is_sick())
        return '+';
    if (person.is_recovered())
        return '-';
    if (person.is_vaccinated())
        return 'O';
    return '?'; // Vaccinated
}

void Simulator::display_population() const {
    std::cout << "Size of population: " << population.persons.size() << '\n'
              << "Day: " << day << '\n';
    for (const auto& person: population.persons) {
        std::cout << get_person_symbol(person) << ' ';
    }
    std::cout << "\n\n";
}

void Simulator::display_statistics() const {
    std::cout << "Nr of sick people: " << population.count_sick() << '\n'
              << "Nr of vaccinated people: " << population.count_vaccinated() << '\n'
              << "Nr of susceptible people: " << population.count_susceptible() << '\n'
              << "Nr of recovered people: " << population.count_recovered() << '\n';
}

void Simulator::pass_one_day() {
    population.spread_infections(SIR, interactions_per_person);
    population.one_more_day();
    ++day;
}

void Simulator::loop() {
    std::string input;

    while (true) {
        system("cls");
        // if (!SIR)
            display_population();
        display_statistics();

        if (population.count_sick() == 0) {
            std::cout << "Final day: " << day << '\n';
            std::cin.get();
            return;
        }

        std::getline(std::cin, input);
        if (input == "q") {
            system("clear");
            return;
        }
        
        pass_one_day();
    }
}

void Simulator::run(bool SIR_arg, int spread_rate = 0) {
    SIR = SIR_arg;
    interactions_per_person = spread_rate;
    population.random_infection(Disease{5, 0.5f}, 1 / (1.0 * population.persons.size()));
    // population.random_vaccination(10/50.0f);
    // population.persons[0].infect(std::make_shared<Disease>(1, 0.5f));
    population.one_more_day();
    loop();
}