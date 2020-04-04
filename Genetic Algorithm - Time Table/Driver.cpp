#include "3. Population.h"
#include "4. Filing.h"

/* These values are the main controls */
/*----------------------------------------------*/
// We are going to use this for mutation of genes
// 1000 = 100% -> 1 = .01% mutation rate
constexpr int MUTATION_RATE = 100;
// Number of parents for cross-over
constexpr int ELIGIBLE_PARENTS = 100;
// Our defined population size
// Should be greater than "(2ELIGIBLE_PARENTS)"
constexpr int POPULATION_SIZE = 5000;
/*----------------------------------------------*/
int fitn = 0;
int fitnCount = 0;
bool fitnprocess = false;
int totalFitness = 0;

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
		if (population.members.at(0).fitnessOfDNA == fitn) {
			fitnCount++;
			if(fitnCount==10) {
				fitnprocess = true;
				break;
			}
		} else if(fitn != population.members.at(0).fitnessOfDNA) { fitn = population.members.at(0).fitnessOfDNA; }


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
	if(fitnprocess) { std::cout << "\nFitness is not changing: " << fitn << " -> Highest Fitness\n"; }

	return 0;
}
