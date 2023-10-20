#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "kamd.h"
#include "otikutils.h"

int decoder(std::string,std::string);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "command should include a file name argument\n";
        return 0;
    }
    std::string path(argv[1]);
    std::string output(argv[2]);
    decoder(path,output);
    return 0;
}

int decoder(std::string path,std::string output) {
    std::ifstream fileIn(path.c_str(), std::ios::in | std::ios::binary);
    if (!fileIn.good()) {
        std::cout << "File not found" << std::endl;
        return 0;
    }

    kamd_header header;
    char sig[4];
    fileIn.read(sig, 4);
    if (sig[0] != 0x4b || sig[1] != 0x61 || sig[2] != 0x4D || sig[3] != 0x64) {
        std::cout << "signature mismatch\n";
        return 0;
    }

    fileIn.seekg(4, std::ios::beg);
    fileIn.read((char*)header.version, 2);
    fileIn.read((char*)header.comp_method, 2);
    fileIn.read((char*)header.intf_protection, 2);
    unsigned char temp[4];
    fileIn.read((char*)temp, 4);
    header.file_size = lendian2int(temp);
    fileIn.read((char*)temp, 2);
    header.filename_size = lendian2sint(temp);
    fileIn.read((char*)temp, 2);
    header.c_overhead_size = lendian2sint(temp);
    fileIn.read((char*)temp, 2);
    header.i_overhead_size = lendian2sint(temp);

    //char* filename = new char[header.filename_size + 1];
    //fileIn.seekg(20,std::ios::beg);
    //fileIn.read(filename, header.filename_size);
    //filename[header.filename_size] = '\0';
   
    std::ofstream fileOut(output.c_str(), std::ios::out | std::ios::binary);
    if (!fileOut.good()) {
        std::cout << "couldn't open/create " << output << '\n';
        return 0;
    }
    //delete[] filename;

    if (*((uint16_t*)header.comp_method) == 0 && *((uint16_t*)header.intf_protection) == 0) {
        int chunk_size = header.file_size > 64 * 1024 ? 64 * 1024 : header.file_size;
        std::vector<unsigned char> buffer(chunk_size);
        fileIn.seekg(20 + header.filename_size + header.c_overhead_size + header.i_overhead_size, std::ios::beg);
		  while (fileIn.good()) {
			  fileIn.read((char*)buffer.data(), chunk_size);
			  std::streamsize s = fileIn.gcount();
			  if (s > 0) {
				  fileOut.write((char*)buffer.data(), s);
			  }
		  }
    }

    fileIn.close();
    fileOut.close();
    return 1;
}
