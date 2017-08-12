/**
 * \file Piecewise_Linear_Density.cpp
 * \date 27-Jul-2017
 *
 * \brief Problem 4 of Chapter 2 in Explorations in Monte Carlo Methods
 *
 * \details Rethought doing it by aliasing as described in the book because
 * the C++ standard library provides the piecewise linear distribution.
 */

#include <val/montecarlo/MonteCarloSim_beta.h>
#include <val/montecarlo/Histogram.h>
#include <val/montecarlo/Chronology.h>
#include <fstream>

int main() {

    Histogram<double, double> histogram(0.0, 15.0, 0.5);

    const double normalizing_constant = 40.0 / 61.0;

    std::vector<double> intervals {0.0, 1.0, 3.0, 6.0, 15.0};
    std::vector<double> weights { 0.0 * normalizing_constant,
                                  1.0/4.0 * normalizing_constant,
                                  1.0/4.0 * normalizing_constant,
                                  1.0/20.0 * normalizing_constant,
                                  1.0/20.0 * normalizing_constant};

    Distribution<double, double, std::piecewise_linear_distribution> distribution(
            intervals.begin(), intervals.end(), weights.begin(), 20);

    auto condition_met = [&histogram](
            Distribution<double, double, std::piecewise_linear_distribution>& _distribution,
            double& iv,
            DRE& dre) -> bool {

        for ( double element : _distribution.events )
            histogram.increment_if_in_range(element);

        iv = _distribution.sum() / static_cast<double>(_distribution.events.size());

        return true;
    };

    MonteCarloSimulation<double, double, double, std::piecewise_linear_distribution>
            monteCarloSimulation(
            1'000'000,
            1,
            condition_met,
            distribution
    );


    monteCarloSimulation.show_distribution();

    StopWatch stopWatch;

    monteCarloSimulation.run();

    stopWatch.stop();

    std::ofstream histogram_file("/home/graph/histogram.txt");
    histogram_file << histogram << '\n';

    monteCarloSimulation.change_message(std::string("weighted average = "));

    monteCarloSimulation.print_result();
}