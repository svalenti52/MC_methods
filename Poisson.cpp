/**
 * \file Poisson.cpp
 * \date 13-Aug-2017
 *
 * \brief Chapter 2, Problem 3.
 */

#include <random>
#include <val/montecarlo/MonteCarloSim_beta.h>

using POISSON = Distribution<int, double, std::poisson_distribution>;

int main() {

    const double mean = 0.3 * 30.0;
    const int nr_events = 20;

    POISSON distribution(mean, nr_events);

    auto condition_met = [nr_events](
            POISSON& _distribution,
            double& iv,
            DRE& dre) -> bool {

        _distribution.reload_random_values(dre);

        iv = static_cast<double>(_distribution.sum()) /static_cast<double>(nr_events);

        return true;
    };

    MonteCarloSimulation<int, double, double, std::poisson_distribution>
            monteCarloSimulation(
                1'000,
                1,
                condition_met,
                distribution);

    monteCarloSimulation.run();

    monteCarloSimulation.change_message("The mean is = ");

    monteCarloSimulation.print_result();

    monteCarloSimulation.show_distribution();
}