#include "3. Population.h"
#include "4. Filing.h"
#include "Improve.h"

/* These values are the main controls */
/*----------------------------------------------*/
// We are going to use this for mutation of genes
// 1000 = 100% -> 1 = .01% mutation rate
constexpr int MUTATION_RATE = 100; // 1% Mutation
// Number of parents for cross-over
constexpr int ELIGIBLE_PARENTS = 40; // Means 80
// Our defined population size
// Should be greater than "(2ELIGIBLE_PARENTS)"
constexpr int POPULATION_SIZE = 100;
/*----------------------------------------------*/
constexpr int ALLOWED_REPETITION = 1;
int currentMaxFitness = 0;
int repeatCount = 0;
int totalFitness = 0;
// Stop when there is no improvement
bool stopAlgorithm = false;
// ------Above is the Guage Cluster for Algorithm

auto main() -> int   {
	// So that everything goes totally randomized
#pragma warning( disable : 4244 )
	srand(time(NULL));

	// Loading all files
	doFiling("1. registration.data", "2. capacity.room", "3. general.info");
	
	// Our population containing random DNA
	// Every single DNA in the population is
	// randomized and its fitness is set to 0
	Population population(POPULATION_SIZE);

	bool goal = false;
	int currentGeneration = 0;

	// Fittest index
	int fitIndex = 0;

	// Fittest DNA
	DNA fit;

	while (!goal) {
		currentGeneration++;
		totalFitness = 0;
		// Clear out the fitness here and then reevaluate for each member, also check if fitness has reached maximum
		for (int i = 0; i < POPULATION_SIZE; i++) {
			population.members.at(i).guageDNAfitness();
			totalFitness = totalFitness + population.members.at(i).fitnessOfDNA;
			if (population.members.at(i).fitnessOfDNA == MAX_FITNESS_DNA) {
				fitIndex = i;
				fit = population.members.at(i);
				goal = true;
				break;
			}
		}

		// Let's sort the whole population from highest to lowest
		// according to their value of fitness (just for cross-over)
		sortPopulation(population);

		// Displaying data of current generation
		std::cout << std::endl << "Generation " << currentGeneration << ", Max fitness is: " << population
		                                                                                        .members.at(0).
		                                                                                        fitnessOfDNA <<
			"/" << MAX_FITNESS_DNA << std::endl;

		// Checking if fitness is not changing
		// If 10 generations are same then stop
		// the algorithm then apply local search
		if (population.members.at(0).fitnessOfDNA == currentMaxFitness) {
			repeatCount++;
			if (repeatCount == ALLOWED_REPETITION) {
				// Storing the fittest as the population is sorted
				fit = population.members.at(0);
				stopAlgorithm = true;
				break;
			}
		}
		else if (currentMaxFitness != population.members.at(0).fitnessOfDNA) {
			currentMaxFitness = population.members.at(0).fitnessOfDNA;
			repeatCount = 0;
		}


		// Choose 'x' number of parents with highest
		// fitness from the population for cross-over
		std::vector<DNA> candidates = eligibleParents(population, ELIGIBLE_PARENTS);
		// Doing some mutation and mating according to above parameters
		doMating(candidates, MUTATION_RATE, totalFitness);
		// Replacing children
		for (int i = 0; i < ELIGIBLE_PARENTS; i++) { population.members.pop_back(); }
		for (int i = 0; i < ELIGIBLE_PARENTS; i++) { population.members.push_back(candidates.at(i)); }
		// Clearing Memory from children
		candidates.clear();

		// goal = true; //For debugging purposes
	}
	
	if (goal) { std::cout << "\nMax fitness is : " << fit.fitnessOfDNA << "\n"; }
	if (stopAlgorithm) {
		std::cout << "\nFitness is not changing: " << currentMaxFitness << " -> Highest Fitness\n";
		std::cout << "Now, applying local search.\n";
		localSearch(fit);
		if (fit.fitnessOfDNA == MAX_FITNESS_DNA) {
			std::cout << "\nPerfect fitness achieved using Local Search which is: " << fit.fitnessOfDNA << "\n";
		}
		else { std::cout << "\nFitness after applying Local Search is: " << fit.fitnessOfDNA << "\n"; }
	}

	return 0;
}
