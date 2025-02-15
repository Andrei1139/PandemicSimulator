#pragma once
#include "population.hpp"
#include <iostream>

class Simulator {
    public:
        using Symbol = char;

        Simulator(const Simulator&) = delete;
        Simulator operator=(const Simulator&) = delete;
        static Simulator& instance(const Population& population) {
            static Simulator simulator{population};
            return simulator;
        }
        void run(bool, int);
        void loop();
        void display_population() const;
        void display_statuses() const;
        void display_statistics() const;
        void pass_one_day();

    private:
        Simulator(const Population& population_arg): population{population_arg} {}
        Population population;
        size_t day{1};
        Symbol get_person_symbol(const Person&) const;
        bool SIR;
        int interactions_per_person{};

};