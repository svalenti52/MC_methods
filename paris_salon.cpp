/**
 * \file paris_salon.cpp
 * \date 11-Jul-2017
 *
 * \brief Expected number of rolls till a 6 is 6. Does making an even stakes
 * bet on 4 rolls not making a 6 make sense?
 *
 */

#include <val/montecarlo/MonteCarloSim.h>
#include <val/montecarlo/Chronology.h>
#include <algorithm>

using DIST = DistributionType;

int main() {

    Distribution<int, DIST::UniformIntegral> four_rolls(1, 6, 4);

    auto condition_met = [] (Distribution<int, DIST::UniformIntegral>& i_four_rolls,
                            double& iv) ->bool {

        auto count_if_six = std::count(i_four_rolls.events.begin(), i_four_rolls.events.end(), 6);

        return count_if_six == 0;
    };

    MonteCarloSimulation_redo<int, double, DIST::UniformIntegral> monteCarloSimulation(
            10'000'000,
            condition_met,
            four_rolls
    );

    StopWatch stopWatch;

    monteCarloSimulation.run();

    stopWatch.stop();

    monteCarloSimulation.print_result();
}
