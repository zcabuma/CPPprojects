// in this program there is: 
// 1. a weather API that provides temperature every 2 seconds (it mimics an externla weather API)
// 2. a display API that contacts the weather API to diplay it 

#include<iostream>
#include<thread>
#include<map>
#include<string>
using namespace std;

std::map<std::string, int> cacheForTemperatures;

// this is a function that tries to mimic an external API call to retrieve data about weather for three cities 
// for demonstration purposes the temperatures move up by one position 
void getUpdatedDataFromAPI(){
    while(true){
        for(auto& item : cacheForTemperatures){
            item.second++;
            std::cout << item.first << " - " << item.second << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
    
}

// here we set the values for the cities and initiate the process of getting an update on the weather
int main()
{
    cacheForTemperatures["London"] = 5;
    cacheForTemperatures["Birmingham"] = 7;
    cacheForTemperatures["Glasgow"] = -2;

    std::thread t1(getUpdatedDataFromAPI);

    t1.join();

    return 0;

}

// Adapted from code written by: https://www.youtube.com/watch?v=xPqnoB2hjjA