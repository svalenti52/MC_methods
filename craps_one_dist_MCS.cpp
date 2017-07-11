/**
 * \file craps_one_dist_MCS.cpp
 * \date 4-Jul-2017
 *
 */

#include <val/montecarlo/MonteCarloSim.h>
#include <val/util.h>

using DIST = DistributionType;

int main() {

    const int nr_events_per_roll_sequence = 2;

    Distribution<int, DIST::UniformIntegral> dice(1, 6, nr_events_per_roll_sequence);
    Distribution<int, DIST::UniformIntegral> blank(1, 6, 0);


    auto condition_met = [](
            Distribution<int, DIST::UniformIntegral>& i_dice,
            Distribution<int, DIST::UniformIntegral>& i_blank,
            double& iv) -> bool {

        int sum = i_dice.sum();

        if (sum == 7 || sum == 11) return true;
        else if (sum ==2 || sum ==3 || sum ==12) return false;

        int point = sum;

        while ( true ) {

            i_dice.reload_random_values();

            sum = i_dice.sum();

            if ( sum == point ) return true;
            else if ( sum == 7 ) return false;
        }
    };

    MonteCarloSimulation<int, int, DIST::UniformIntegral, DIST::UniformIntegral>
            monteCarloSimulation(
            10'000'000,
            condition_met,
            dice,
            blank
    );

    StopWatch stopWatch;

    monteCarloSimulation.run();

    stopWatch.stop();

    monteCarloSimulation.print_result();
}
