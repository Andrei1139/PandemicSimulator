#include <iostream>
#include <vector>
#include <algorithm>
#include "person.hpp"
#include "disease.hpp"
#include "population.hpp"
#include "simulator.hpp"
#include "utils.hpp"

int main() {
    std::system("cls");

    Population pop{100};
    auto& simulator = Simulator::instance(pop);
    simulator.run(true, 5);
    
    return 0;
}