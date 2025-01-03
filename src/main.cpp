#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include "ProgressBar/ProgressBar.h"

/**
 * Convert file to bytecode and save it to .h file
 * @param input_path Path to input file
 * @param output_path Path to output file (optional)
 * @return true if conversion successful, false otherwise
 */
bool convertToByteCode(const std::string &input_path, std::string output_path = "")
{
    // Open input file in binary mode
    std::ifstream input(input_path, std::ios::binary);
    if (!input.is_open())
    {
        std::cerr << "Error: Failed to open input file" << std::endl;
        return false;
    }

    // Get file size
    input.seekg(0, std::ios::end);
    size_t file_size = input.tellg();
    input.seekg(0, std::ios::beg);

    // Read file content into vector
    std::vector<unsigned char> buffer(file_size);
    ProgressBar progress;

    std::cout << "Reading file..." << std::endl;
    for (size_t i = 0; i < file_size; ++i)
    {
        buffer[i] = input.get();
        if (i % (file_size / 100 + 1) == 0)
        {
            progress.update(i, file_size);
        }
    }
    progress.finish();
    input.close();

    // Generate output path if not specified
    if (output_path.empty())
    {
        output_path = std::filesystem::path(input_path).stem().string() + ".h";
    }

    std::ofstream output(output_path);
    if (!output.is_open())
    {
        std::cerr << "Error: Failed to create output file" << std::endl;
        return false;
    }

    // Write array declaration
    std::string array_name = std::filesystem::path(input_path).filename().stem().string() + "_data";
    // Remove all characters except letters, numbers and underscores
    array_name.erase(std::remove_if(array_name.begin(), array_name.end(),
                                    [](char c)
                                    {
                                        return !(std::isalnum(c) || c == '_');
                                    }),
                     array_name.end());
    // If first character is a number, add prefix
    if (!array_name.empty() && std::isdigit(array_name[0]))
    {
        array_name = "data_" + array_name;
    }
    output << "constexpr unsigned int " << array_name << "[] = {";

    std::cout << "Converting to bytecode..." << std::endl;
    for (size_t i = 0; i < buffer.size(); ++i)
    {
        if (i % 12 == 0)
            output << "\n    ";
        output << "0x" << std::hex << static_cast<int>(buffer[i]);
        if (i < buffer.size() - 1)
            output << ", ";

        if (i % (buffer.size() / 100 + 1) == 0)
        {
            progress.update(i, buffer.size());
        }
    }
    progress.finish();

    output << "\n};\n\n";
    output << "constexpr size_t " << array_name << "_size = sizeof(" << array_name << ");\n";
    output.close();

    return true;
}

int main(int argc, char *argv[])
{
    std::string input_path;

    if (argc > 1)
    {
        input_path = argv[1];
    }
    else
    {
        std::cout << "Please enter the file path: ";
        std::getline(std::cin, input_path);
    }

    if (input_path.empty())
    {
        std::cerr << "Error: File path not specified" << std::endl;
        return 1;
    }

    std::string output_path = "";
    if (argc > 2)
    {
        output_path = argv[2];
    }

    if (convertToByteCode(input_path, output_path))
    {
        std::cout << "Conversion completed successfully!" << std::endl;
        return 0;
    }

    return 1;
}