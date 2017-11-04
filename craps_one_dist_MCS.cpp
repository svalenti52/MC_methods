/**
 * \file craps_one_dist_MCS.cpp
 * \date 4-Jul-2017
 *
 */

#include <val/montecarlo/MonteCarloSim_beta.h>
#include <val/util.h>

using UNIFORM_INTEGRAL_PARAMS = Distribution<int, int, std::uniform_int_distribution>;

int main() {

    const int nr_events_per_roll_sequence = 2;

    UNIFORM_INTEGRAL_PARAMS dice(1, 6, nr_events_per_roll_sequence);

    auto condition_met = [](
            UNIFORM_INTEGRAL_PARAMS& i_dice,
            double& iv,
            DRE& dre) -> bool {

        const bool Won = true;
        const bool Lost = false;

        int sum = i_dice.sum();

        if (sum == 7 || sum == 11) return Won;
        if (sum ==2 || sum ==3 || sum ==12) return Lost;

        int point = sum;

        while ( true ) {

            i_dice.reload_random_values(dre);

            sum = i_dice.sum();

            if ( sum == point ) return Won;
            if ( sum == 7 ) return Lost;
        }
    };

    MonteCarloSimulation<int, double, int, std::uniform_int_distribution>
            monteCarloSimulation(
            10'000'000,
            1,
            condition_met,
            dice
    );

    StopWatch stopWatch;

    monteCarloSimulation.run();

    stopWatch.stop();

    monteCarloSimulation.print_result();
}
