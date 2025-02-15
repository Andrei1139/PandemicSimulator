#include "population.hpp"

Population::Population(std::initializer_list<std::string_view> names) {
    persons.reserve(names.size());
    for (auto name: names) {
        persons.push_back(Person{name});
    }
}

void Population::random_infection(Disease disease, float percentage) {
    auto disease_ptr = std::make_shared<Disease>(disease);
    int nr = static_cast<int>(percentage * persons.size());
    for (auto i = 0; i < nr; ++i) {
        int pos = get_random_int(persons.size());
        if (persons[pos].is_infected()) {
            --i;
            continue;
        }
        persons[pos].infect(disease_ptr);
    }
}

void Population::random_vaccination(float percentage) {
    int nr = static_cast<int>(percentage * persons.size());
    for (auto i = 0; i < nr; ++i) {
        int pos = get_random_int(persons.size());
        if (persons[pos].is_vaccinated()) {
            --i;
            continue;
        }
        persons[pos].vaccinate();
    }
}

int Population::count_sick() const {
    int count{};
    for (const auto& person: persons) {
        count += person.is_sick();
    }
    return count;
}

int Population::count_vaccinated() const {
    int count{};
    for (const auto& person: persons) {
        count += person.is_vaccinated();
    }
    return count;
}

int Population::count_susceptible() const {
    int count{};
    for (const auto& person: persons) {
        count += person.is_susceptible();
    }
    return count;
}

int Population::count_recovered() const {
    int count{};
    for (const auto& person: persons) {
        count += person.is_recovered();
    }
    return count;
}

int Population::count_infected() const {
    int count{};
    for (const auto& person: persons) {
        count += person.is_infected();
    }
    return count;
}

void Population::one_more_day() {
    for (auto& person: persons) {
        person.one_more_day();
    }
}

void Population::spread_infections(bool randomized, int spread_rate = 0) {
    if (persons.size() < 2) return;
    if (randomized) {
        for (size_t i = 0; i < persons.size(); ++i) {
            if (persons[i].is_sick()) {
                touch_random_people(i, spread_rate);
            }
        }
        return;
    }
    for (size_t i = 0; i < persons.size() - 1; ++i) {
        persons[i].touch(persons[i + 1]);
    }
}

void Population::touch_random_people(int person_index, int n) {
    size_t last_index = indexes.size() - 1;
    while (last_index >= indexes.size() - n) {
        size_t i = get_random_int(last_index);
        if (indexes[i] == person_index)
            continue;
        persons[person_index].touch(persons[indexes[i]]);
        std::swap(indexes[last_index], indexes[i]);
        --last_index;
    }
}