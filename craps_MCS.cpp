/**
 * \file craps_MCS.cpp
 * \date 4-Jul-2017
 *
 */

#include <val/montecarlo/MonteCarloSim.h>

using DIST = DistributionType;

int main() {

    const int nr_events_per_roll_sequence = 1;

    Distribution<int, DIST::UniformIntegral> die1(1, 6, nr_events_per_roll_sequence);
    Distribution<int, DIST::UniformIntegral> die2(1, 6, nr_events_per_roll_sequence, 373);

    auto condition_met = [](
            Distribution<int, DIST::UniformIntegral>& i_die1,
            Distribution<int, DIST::UniformIntegral>& i_die2,
            double& iv) -> bool {

        bool won = false;
        bool no_result = true;

        int sum = i_die1.events[0]+i_die2.events[0];

        if (sum == 7 || sum == 11) {
            won = true;
            no_result = false;
        }
        else if (sum ==2 || sum ==3 || sum ==12) {
            won = false;
            no_result = false;
        }

        int point = sum;

        while (no_result) {

            i_die1.reload_random_value(0);
            i_die2.reload_random_value(0);

            sum = i_die1.events[0] + i_die2.events[0];

            if ( sum == point ) {
                won = true;
                no_result = false;
            }
            if ( sum == 7 ) {
                won = false;
                no_result = false;
            }
        }

        //i_die2.reload_random_values();
        return won;
    };

    MonteCarloSimulation<int, int, DIST::UniformIntegral, DIST::UniformIntegral>
            monteCarloSimulation(
                    10'000'000,
                    condition_met,
                    die1,
                    die2
            );

    monteCarloSimulation.run_2_distributions();

    monteCarloSimulation.print_result();
}
