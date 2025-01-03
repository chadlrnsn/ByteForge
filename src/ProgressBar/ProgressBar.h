#pragma once

#include <iostream>
#include <iomanip>

/**
 * Simple progress bar for console output
 */
class ProgressBar
{
    int width;
    char fill_char;
    char empty_char;

public:
    ProgressBar(int width = 50, char fill = '=', char empty = '-');
    void update(size_t current, size_t total);
    void finish();
};

