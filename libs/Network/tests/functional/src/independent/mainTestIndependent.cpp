/*
** EPITECH PROJECT, 2021
** mainTestIndependant.cpp
** File description:
** TODO: add description
*/

#include <functional>
#include <stdexcept>
#include <string>
#include "independentTest.hpp"
#include <unordered_map>

/**
 * @brief A sample test function to be copied for other tests
 * @return 0 if succeed
 */
int testFunction()
{
    if (0 == 84)
        return 84;
    return 0;
}

static const std::unordered_map<int, std::function<int(void)>> testFunctions{{0, testFunction},
    {1, testTramBufferComplete}, {2, testTramBufferIncomplete}, {3, testTramBufferTruncatedSet},
    {4, testTramBuffer2Sets}};

int main(int ac, char **av)
{
    if (ac != 2)
        throw std::invalid_argument("Test should only take test number as parameter");
    int functionNumber(std::stoi(av[1]));

    return testFunctions.at(functionNumber)();
}