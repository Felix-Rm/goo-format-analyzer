#include <iostream>

#include "goo_defs.hpp"

int main(int argc, char* argv[]) {
  try {
    auto options = goo::parse_cli(argc, argv);

    auto goo_file_data = goo::read_file(options.input_file);
    auto goo_file = goo::unpack_file(goo_file_data.as_span());

    goo::print_file(goo_file, options);

  } catch (std::runtime_error& error) {
    std::cerr << error.what() << std::endl;
    return 1;
  }

  return 0;
}