#include <fstream>
#include <iostream>

#include "goo_defs.hpp"

util::dynamic_array<uint8_t> goo::read_file(std::string filename) {
  std::ifstream file(filename, std::ios::binary);

  if (!file.is_open()) {
    auto error = std::string("Error: Could not open file ") + filename;
    throw std::runtime_error(error);
  }

  file.seekg(0, std::ios::end);
  util::dynamic_array<uint8_t> buffer(file.tellg());

  file.seekg(0, std::ios::beg);
  file.read((char*)buffer.data(), buffer.size());

  file.close();

  return buffer;
}