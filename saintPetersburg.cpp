/**
 * \file saintPetersburg.cpp
 * \date 5-Jul-2017
 *
 */

#include <val/montecarlo/MonteCarloSim.h>
#include <val/montecarlo/Histogram.h>
#include <fstream>

using DIST = DistributionType;

int main() {

    Distribution<bool, DIST::BernoulliIntegral> coin(0.5, 1, 7);
    Distribution<int, DIST::UniformIntegral> state(1, 6, 0);

    const int nr_trials = 4'000;

    Histogram<int, double> histogram(0, nr_trials, 1);

    int discrete_time = 1;

    auto condition_met = [&discrete_time, &histogram](Distribution<bool, DIST::BernoulliIntegral>& _coin,
                            Distribution<int, DIST::UniformIntegral>& _state,
                            double& stake) -> bool {

        stake -= 5.0;

        double winnings = 1.0;

        while ( _coin.events[0] ) {
            stake += winnings;
            winnings *= 2.0;
            _coin.reload_random_values();
        }

        histogram.add_to_bin(discrete_time, stake);
        ++discrete_time;
        return true;
    };

    MonteCarloSimulation<bool, int, DIST::BernoulliIntegral, DIST::UniformIntegral> monteCarloSimulation(
            nr_trials,
            condition_met,
            coin,
            state
    );

    monteCarloSimulation.run();

    monteCarloSimulation.print_result();

    std::ofstream histogram_file("/home/graph/histogram.txt");
    histogram_file << histogram << '\n';

}