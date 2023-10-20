#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "kamd.h"
#include "otikutils.h"


void coder(std::string,std::string output, kamd_header *header);

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cout << "command should include a file name and an output name\n";
    return 0;
  }
  std::string path(argv[1]);
  std::string output(argv[2]);
  kamd_header header;
  coder(path, output, &header);
  return 0;
}

void coder(std::string path,std::string output, kamd_header* header) {
  std::ifstream fileIn(path.c_str(), std::ios::in | std::ios::binary);
  if (!fileIn.good()) {
    std::cout << "File not found" << std::endl;
    return;
  }

  header->file_size = fileIn.tellg();
  fileIn.seekg(0, std::ios::end);
  header->file_size = (uint32_t)fileIn.tellg() - header->file_size;
  fileIn.seekg(0, std::ios::beg);


  std::string filename = path.substr(path.find_last_of("/\\") + 1);
  header->filename_size = filename.length();

  std::ofstream fileOut(output.c_str(), std::ios::out | std::ios::binary);
  if (!fileOut.good()) {
    std::cout << "couldn't open/create " << output << '\n';
    return;
  }

  fileOut.write((char*) header->signature, 4);
  fileOut.write((char*) header->version, 2);
  fileOut.write((char*) header->comp_method, 2);
  fileOut.write((char*) header->intf_protection, 2);
  fileOut.write((char*)int2lendian(header->file_size), 4);
  fileOut.write((char*)sint2lendian(header->filename_size), 2);
  fileOut.write((char*)sint2lendian(header->c_overhead_size), 2);
  fileOut.write((char*)sint2lendian(header->i_overhead_size), 2);
  fileOut.write(filename.c_str(), header->filename_size);
  if (header->c_overhead_size) {
      // write overhead
  }
  if (header->i_overhead_size) {
      // write overhead
  }

  int chunk_size = header->file_size > 64 * 1024 ? 64 * 1024 : header->file_size;
  std::vector<unsigned char> buffer(chunk_size);
  while (fileIn.good()) {
      fileIn.read((char*)buffer.data(), chunk_size);
      std::streamsize s = fileIn.gcount();
      if (s > 0) {
          fileOut.write((char*)buffer.data(), s);
      }
  }
  fileIn.close();
  fileOut.close();
}
