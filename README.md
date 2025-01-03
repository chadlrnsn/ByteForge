# ByteForge

A simple command-line tool that converts any file into a C/C++ header file containing the file's contents as bytecode.

## Features

- Convert any file to bytecode array in a header file
- Progress bar visualization during conversion
- Support for drag-and-drop or command-line arguments
- Automatic safe variable naming
- Real-time conversion progress display

## Usage

```bash
# Using command line arguments
ByteForge input_file [output_file.h]

# Interactive mode
ByteForge
> Please enter the file path: input_file
```

The tool will generate a header file containing:
- An unsigned int array with the file's bytecode
- A constant with the array size

## Output Example

```cpp
unsigned int example_data[] = {
    0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
    // ... more bytes ...
};

const size_t example_data_size = sizeof(example_data);
``` 