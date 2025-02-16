#pragma once
#include "person.hpp"
#include "utils.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

float get_random_float();
int get_random_int(int);

class Population {
    public:
        explicit Population(int n) {
            persons.resize(n);
            indexes.resize(n);
            std::iota(indexes.begin(), indexes.end(), 0);
        }
        Population(std::initializer_list<std::string_view>);
        Population(): Population{1} {}
        void random_infection(Disease, float);
        void random_vaccination(float);
        int count_infected() const;
        int count_sick() const;
        int count_vaccinated() const;
        int count_susceptible() const;
        int count_recovered() const;
        void one_more_day();
        void spread_infections(bool, int);

        std::vector<Person> persons;

    private:
        void touch_random_people(int, int);
        std::vector<int> indexes;
};

