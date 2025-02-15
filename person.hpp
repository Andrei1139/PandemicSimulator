#pragma once
#include "disease.hpp"
#include "utils.hpp"
#include <iostream>
#include <string_view>
#include <memory>

class Person {
    public:
        explicit Person(std::string_view name_arg): name{name_arg} {}
        Person(): Person{"TestSubject"} {}
        std::string status_string() const;
        void one_more_day();
        void infect(const std::shared_ptr<Disease>&);
        void vaccinate() {status = Status::VACCINATED; days_until_recovery = 0;}
        int get_duration() const {return days_until_recovery;}

        bool is_recovered() const {return status == Status::RECOVERED;}
        bool is_susceptible() const {return status == Status::SUSCEPTIBLE;}
        bool is_sick() const {return status == Status::SICK;}
        bool is_vaccinated() const {return status == Status::VACCINATED;}
        bool is_infected() const {return status == Status::INFECTED;}

        void touch(Person&);

    private:
        enum class Status {
            SICK, SUSCEPTIBLE, RECOVERED, VACCINATED, INFECTED
        };
        Status status{Status::SUSCEPTIBLE};
        int days_until_recovery{};
        std::string name;
        std::shared_ptr<Disease> disease{nullptr};

};