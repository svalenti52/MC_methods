/**
 * \file Piecewise_Linear_Density.cpp
 * \date 27-Jul-2017
 *
 * \brief Problem 4 of Chapter 2 in Explorations in Monte Carlo Methods
 *
 * \details Rethought doing it by aliasing as described in the book because
 * the C++ standard library provides the piecewise linear distribution.
 */

#include <val/montecarlo/MonteCarloSim_alpha.h>
#include <val/montecarlo/Histogram.h>
#include <fstream>

using DIST = DistributionType;

int main() {

    Histogram<double, double> histogram(0.0, 15.0, 0.5);

    const double normalizing_constant = 40.0 / 61.0;

    std::vector<double> intervals {0.0, 1.0, 3.0, 6.0, 15.0};
    std::vector<double> weights { 0.0 * normalizing_constant,
                                  1.0/4.0 * normalizing_constant,
                                  1.0/4.0 * normalizing_constant,
                                  1.0/20.0 * normalizing_constant,
                                  1.0/20.0 * normalizing_constant};

    Distribution<double, DIST::PiecewiseLinearReal> distribution(
            intervals.begin(), intervals.end(), weights.begin(), 20);

    auto condition_met = [&histogram](
            Distribution<double, DIST::PiecewiseLinearReal>& _distribution,
            double& iv,
            DRE& dre) -> bool {

        for ( double element : _distribution.events )
            histogram.increment_if_in_range(element);

        return true;
    };

    MonteCarloSimulation<double, double, DistributionType::PiecewiseLinearReal>
            monteCarloSimulation(
            200,
            1,
            condition_met,
            distribution
    );

    monteCarloSimulation.show_distribution();

    monteCarloSimulation.run();

    std::ofstream histogram_file("/home/graph/histogram.txt");
    histogram_file << histogram << '\n';

}