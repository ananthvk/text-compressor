#include "block_archiver.hpp"
#include "huffman.hpp"
#include <errno.h>
#include <fstream>
#include <iostream>
#include <string.h>

// Buffer size 64KB
#define BUFFER_SIZE 64000

int main(int argc, char *argv[])
{
    HuffmanArchiver huff;
    BlockArchiver &archiver = huff;
    bool is_current_mode_compression = true;

    if (argc < 4)
    {
        std::cerr << "Usage: ./archiver compress|decompress <input_file> <output_file>"
                  << std::endl;
        exit(1);
    }

    if (std::string(argv[1]) == "compress")
        is_current_mode_compression = true;
    else if (std::string(argv[1]) == "decompress")
        is_current_mode_compression = false;
    else
    {
        std::cerr << "Invalid operation, specify either compress or decompress" << std::endl;
        exit(1);
    }

    std::ifstream ifs(argv[2], std::ifstream::binary);
    if (!ifs)
    {
        std::cerr << "Error while opening input file: " << strerror(errno) << std::endl;
        exit(1);
    }

    std::ofstream ofs(argv[3], std::ofstream::binary);
    if (!ifs)
    {
        std::cerr << "Error while opening output file: " << strerror(errno) << std::endl;
        exit(1);
    }

    bytes buffer(BUFFER_SIZE, 0);

    while (ifs.read(reinterpret_cast<char *>(buffer.data()), buffer.size()) || ifs.gcount() > 0)
    {
        uint64_t bytes_read = ifs.gcount();
        bytes processed;
        if (is_current_mode_compression)
            processed = archiver.compress(buffer.begin(), buffer.begin() + bytes_read);
        else
            processed = archiver.decompress(buffer.begin(), buffer.begin() + bytes_read);

        ofs.write(reinterpret_cast<char *>(processed.data()), processed.size());
        if (ofs.bad())
        {
            std::cerr << "Error while writing to output file: " << strerror(errno) << std::endl;
            exit(1);
        }
    }
    // Check if an error occured
    if (ifs.bad())
    {
        std::cerr << "Error while reading input file: " << strerror(errno) << std::endl;
        exit(1);
    }
    if (ofs.bad())
    {
        std::cerr << "Error while writing to output file: " << strerror(errno) << std::endl;
        exit(1);
    }
}