#include <iostream>
#include <math.h>
#include <random>
#include <vector> 
#include <algorithm>

struct Solution
{
    double rank;
    double a; 
    double b;
    double c;

    void fitness()
    {
        double ans = (6 * a + -b + std::pow(c,200)) - 25;
        if(ans == 0){
            rank = 9999;
        }
        else{
            rank = std::abs(1/ans); // because we want the rank to be inversely prop to distance bw fn and 25 
        }

    }
};

int getOptimalABC()
{

    // important constants
    const int numberOfTopsSolutions = 1000;
    const int numberOfSolutions = 60000; 
    std::random_device device;
    std::uniform_real_distribution<double> unif(-100000,100000);
    std::uniform_int_distribution<int> cross(0,numberOfTopsSolutions-1);
    std::uniform_real_distribution<double> m(0.99,1.01);

    std::vector<Solution> finalSolutions;
    std::vector<Solution> intermediateSolns;
    
    // prepare initial final solutions
    for(int i = 0; i < numberOfSolutions; i++)
        finalSolutions.push_back(Solution{
            0, 
            unif(device),
            unif(device),
            unif(device)
        });

    int roundNumber = 100; 

    while(roundNumber > 0)
    {
        // Run our fitness function for all solutuons 
        for(auto& s : finalSolutions) { s.fitness(); }
        
        // Sort our final_solutions by rank (slower compared to partial sort)
        std::sort(
            finalSolutions.begin(), 
            finalSolutions.end(), 
        [](const auto& lhs,const auto& rhs){
            return lhs.rank > rhs.rank;
        });
        
        // Print top solutions
        std::for_each(
            finalSolutions.begin(), 
            finalSolutions.begin() + 10, [=](const auto& s){
            std::cout << std::fixed 
                << "Rank " << static_cast<int>(s.rank)
                << "\na:" << s.a << " b:" << s.b << " c:" << s.c << " " << roundNumber << " \n";
        });

        // Take top solutions
        // top solutions are alw in the next generation
        // put this in sample
        std::copy(
            finalSolutions.begin(), 
            finalSolutions.begin() + numberOfTopsSolutions,
            std::back_inserter(intermediateSolns)
        );
        finalSolutions.clear();

        // Mutate the top solutions by %
        // change elements in sample a lil bit so we can get solns we couldnt get from the starting elements
        std::for_each(intermediateSolns.begin(), intermediateSolns.end(), [&](auto& s){
            s.a *= m(device);
            s.b *= m(device);
            s.c *= m(device);
        });

        // Cross over
        // combine random top solutions from sample --> add it to solutions 
        for(int i = 0; i < numberOfSolutions; i++)
        {
            finalSolutions.push_back(Solution{
                0,
                intermediateSolns[cross(device)].a,
                intermediateSolns[cross(device)].b,
                intermediateSolns[cross(device)].c,
            });
        }
        intermediateSolns.clear();
	    roundNumber-=1;
    }

}

int main(){
    getOptimalABC();
}


// Adapted from code written by: Top Shelf Technology (https://gist.github.com/TheBuilder-software/11e4018eb33921b5dfb1f059018d6fdd)
