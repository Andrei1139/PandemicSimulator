#include "person.hpp"

std::string Person::status_string() const {
    std::string text{name + " is "};
    switch (status) {
        case Status::RECOVERED:
            text += "recovered";
            break;

        case Status::SUSCEPTIBLE:
            text += "susceptible";
            break;

        case Status::VACCINATED:
            text += "vaccinated";
            break;

        case Status::SICK:
            text += "sick (" + std::to_string(days_until_recovery) + " day"
                   + (days_until_recovery > 1 ? "s" : "") + " to go)";
            break;

        case Status::INFECTED:
            text += "infected";
            break;
    }
    return text;
}

void Person::one_more_day() {
    if (is_infected()) {
        status = Status::SICK;
        days_until_recovery = disease->get_duration();
        return;
    }
    if (days_until_recovery == 0)
        return;
    --days_until_recovery;
    if (days_until_recovery == 0)
        status = Status::RECOVERED;
}

void Person::infect(const std::shared_ptr<Disease>& disease_arg) {
    if (is_susceptible()) {
        disease = disease_arg;
        status = Status::INFECTED;
    }
}

void Person::touch(Person& person) {
    if (person.is_sick()) {
        if (is_sick())
            return;
        person.touch(*this);
        return;
    }
    if (is_sick() && get_random_float() <= disease->get_chance())
        person.infect(disease);
}