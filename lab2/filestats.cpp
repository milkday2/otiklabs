#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

bool sortbyfirst(const std::pair<int,int> &a,
                   const std::pair<int,int> &b)
{
       return a.first>b.first;
}

void task1(std::string path) {
  std::ifstream fileIn(path.c_str(), std::ios::in | std::ios::binary);
  if (!fileIn.good()) {
    std::cout << "File not found" << std::endl;
    return;
  }

  uint32_t file_size = fileIn.tellg();
  fileIn.seekg(0, std::ios::end);
  file_size = (uint32_t)fileIn.tellg() - file_size;
  fileIn.seekg(0, std::ios::beg);

  int freq[256] = {};

  int chunk_size = file_size > 64 * 1024 ? 64 * 1024 : file_size;
  std::vector<unsigned char> buffer(chunk_size);
  while (fileIn.good()) {
      fileIn.read((char*)buffer.data(), chunk_size);
      std::streamsize s = fileIn.gcount();
      if (s > 0) {
          for (int i = 0; i < s; i++)
              freq[buffer[i]]++;
      }
  }
  fileIn.close();

  double p[256];
  double Ia[256];
  for (int i = 0; i < 256; i++) {
      p[i] = ((double) freq[i]) / file_size;
      Ia[i] = - std::log2(p[i]);
  }

  double I = 0.0;
  for (int i = 0; i < 256; i++) {
      I = I + freq[i] * Ia[i];
  }

  std::cout << "index\tfrequency\tp\tIa\n";
  for (int i = 0; i < 256; i++) {
      std::cout << i << '\t' << freq[i] << '\t' << p[i] << '\t' << Ia[i] << '\n';
  }
  
  std::vector<std::pair<int, int>> sorted_freq;
  for (int i = 0; i < 256; i++) {
        sorted_freq.push_back(std::make_pair(freq[i], i));
  }
  std::cout << '\n';
  std::sort(sorted_freq.begin(), sorted_freq.end(), sortbyfirst);

  std::cout << "index\tfrequency\tp\tIa\n";
  for (int i = 0; i < 256; i++) {
      std::cout << sorted_freq[i].second << '\t' << sorted_freq[i].first << '\t' << p[sorted_freq[i].second]
          << '\t' << Ia[sorted_freq[i].second] << '\n';
  }
  std::cout << "I = " << I;

}

