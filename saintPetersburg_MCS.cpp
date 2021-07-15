/**
 * \file saintPetersburg_MCS.cpp
 * \date 14-Jul-2021
 *
 */

#include <val/montecarlo/MonteCarloSim_beta.h>
#include <val/montecarlo/Histogram.h>
#include <fstream>

using COIN_FLIP_PARAMS = Distribution_NTT<bool, double, std::bernoulli_distribution>;

int main()
{
    const int nr_trials = 4'000;
    Histogram<int, double> histogram(0, nr_trials, 1);
    int discrete_time = 1;
    COIN_FLIP_PARAMS coin(0.5, 1);

    auto condition_met = [&histogram, &discrete_time] (
            COIN_FLIP_PARAMS& i_coin,
            double& stake,
            DRE& dre
            ) -> bool {

        stake -= 5.0;
        double winnings = 1.0;

        while (i_coin.events[0])
        {
            stake += winnings;
            winnings *= 2.0;
            i_coin.reload_random_values(dre);
        }
        histogram.add_to_bin(discrete_time, stake);
        ++discrete_time;
        return true;
    };

    MonteCarloSimulation_NTT<bool, double, double, std::bernoulli_distribution>
            monteCarloSimulation(
            nr_trials,
            7,
            condition_met,
            coin
    );

    monteCarloSimulation.run();

    monteCarloSimulation.print_result();

    std::ofstream histogram_file("/home/svale/graph/histogram.txt");
    histogram_file << histogram << '\n';
}
