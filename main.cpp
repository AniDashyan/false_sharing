#include <iostream>
#include <thread>
#include <utility>
#include "kaizen.h"

struct CountersAdjacent {
    int x = 0;
    int y = 1;
};

struct CountersPadded {
   int x = 0;
   char padding[64 - sizeof(int)];
   int y = 0;
};

void increment_counter(int* counter, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        (*counter)++;
    }
}

void run_non_threaded(CountersAdjacent& counters,int iterations, zen::timer& t) {
    t.start();
    increment_counter(&counters.x, iterations);
    increment_counter(&counters.y, iterations);
    t.stop();
    zen::log("Non-threaded time: ", t.duration<zen::timer::usec>().count()," ms");
}

void run_threaded_adjacent(CountersAdjacent& counters,int iterations, zen::timer& t) {
    t.start();
    std::thread t1(increment_counter, &counters.x, iterations);
    std::thread t2(increment_counter, &counters.y, iterations);
    t1.join();
    t2.join();
    t.stop();
    zen::log("Threaded (false sharing) time: " ,t.duration<zen::timer::usec>().count() ," ms");
}

void run_threaded_padded(CountersPadded& counters,int iterations, zen::timer& t) {
    t.start();
    std::thread t1(increment_counter, &counters.x, iterations);
    std::thread t2(increment_counter, &counters.y, iterations);
    t1.join();
    t2.join();
    t.stop();
    zen::log("Threaded (padded) time: " ,t.duration<zen::timer::usec>().count() ," ms");
}

std::pair<int, int> parse_args(int argc, char** argv) {
    zen::cmd_args args(argv, argc);
    int iter = 100'000'000;
    int runs = 5;
    if (!args.is_present("--iter")|| !args.is_present("--runs")) {
        zen::log(zen::color::yellow("No --iter or --runs provided. Using default values: "));
        return {iter, runs};
    } else {
        iter = std::stoi(args.get_options("--iter")[0]);
        runs = std::stoi(args.get_options("--runs")[0]);
    }
    return {iter, runs};
}

int main(int argc, char** argv) {

    auto [iterations, runs] = parse_args(argc, argv);
    CountersAdjacent counters_adjacent;
    CountersPadded counters_padded;
    zen::timer t;

    auto total_non_threaded = 0, total_adjacent = 0, total_padded = 0;

    for (int i = 0; i < runs; ++i) {
        zen::log("\nRun " ,i + 1 ,":");

       
        run_non_threaded(counters_adjacent, iterations, t);
        total_non_threaded += t.duration<zen::timer::usec>().count();
        
    
        run_threaded_adjacent(counters_adjacent, iterations, t);
        total_adjacent += t.duration<zen::timer::usec>().count();
     

        run_threaded_padded(counters_padded, iterations, t);
        total_padded += t.duration<zen::timer::usec>().count();
      
    }

    zen::log("\nAverage times over " ,runs ," runs:");
    zen::log("Non-threaded: " ,total_non_threaded / runs ," ms");
    zen::log("Threaded (false sharing): " ,total_adjacent / runs ," ms");
    zen::log("Threaded (padded): " ,total_padded / runs ," ms");

    return 0;
}