#pragma once
#include <random>
#include <chrono>

//Singelton class
class RandomGenerator
{
private:
    std::mt19937 randomEngine;
	//					this seeds the random generator with the system time as the seed value.
    RandomGenerator() : randomEngine(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count())) {}

public:
    // Delete copy constructor and assignment operator;
	// to prevent copying of our singelton
    RandomGenerator(const RandomGenerator&) = delete;
    RandomGenerator& operator=(const RandomGenerator&) = delete;

    // Static method to get the instance
    static RandomGenerator& getInstance()
    {
        static RandomGenerator instance;
        return instance;
    }

	// Returns a random integer between min and max (min and max are inclusive)
    template <typename type_value>
    type_value getRandomInt(const type_value min, const type_value max)
    {
        std::uniform_int_distribution<type_value> distribution(min, max);
        return (distribution(randomEngine));
    }

	//Returns a random floating-point number between min and max (min inclusive, max exclusive)
    template <typename type_value>
    type_value getRandomReal(const type_value min, const type_value max)
    {
        std::uniform_real_distribution<type_value> distribution(min, max);
        return (distribution(randomEngine));
    }
	/*
	Most existing implementations have a bug where they may occasionally return b (max)
	More info: https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
	*/
};