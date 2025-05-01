#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        // create array to store the 5 values
        unsigned long long w[5] = {0};

        // create an int to store the index of the 5 values you are on
        int index = 4;

        // run a for loop for each index
        for(int i = k.size() - 1; i >= 0 && index >= 0; i -= 6){
            // create a variable to store the exponentialally increasing 36 value
            unsigned long long exponent = 1;

            // create a variable to store the value for the index
            unsigned long long idxval = 0;

            // process 6 characters in the string for the loop if there are 6
            for(int j = 0; i - j >= 0 && j < 6; ++j){
                // store the character
                char character = k[i - j];

                // convert it to HASH_INDEX_T
                HASH_INDEX_T val = letterDigitToNumber(character);

                // add these to the idxval
                idxval += exponent * val;

                // multiply the expontent by 36 (1, 36, 36^2)
                exponent *= 36;
            }

            // add the final idxval to the array
            w[index] = idxval;

            // decremenet the index
            --index;
        }

        // create a variable to store the singular hash value
        unsigned long long final = 0;
        
        // run a look through the 5 stored index values
        for(int i = 0; i < 5; ++i){
            // add the correct calculation
            final += w[i] * rValues[i];
        }
        
        // return the final hash value
        return final;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        // make such re its lower case
        letter = tolower(letter);

        // check if its a number
        if(letter >= '0' && letter <= '9'){
            // return integral value
            return ((letter - '0') + 26);
        }

        // check if its a letter
        if(letter >= 'a' && letter <= 'z'){
            return (letter - 'a');
        }

        // return if its not either
        return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
