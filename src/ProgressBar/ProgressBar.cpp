#include "ProgressBar.h"

ProgressBar::ProgressBar(int width, char fill, char empty)
    : width(width), fill_char(fill), empty_char(empty) {}

void ProgressBar::update(size_t current, size_t total)
{
    float progress = static_cast<float>(current) / total;
    int filled = static_cast<int>(width * progress);

    std::cout << "\r[";
    for (int i = 0; i < width; ++i)
    {
        if (i < filled)
            std::cout << fill_char;
        else
            std::cout << empty_char;
    }
    std::cout << "] " << std::fixed << std::setprecision(1)
              << (progress * 100.0f) << "%" << std::flush;
}

void ProgressBar::finish()
{
    std::cout << std::endl;
}
