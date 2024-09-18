#include <cstring>
#include <iostream>

#include "goo_defs.hpp"

goo::cli_options goo::parse_cli(int argc, char* argv[]) {
  cli_options options{};

  // Default options
  options.output_dir = "goo_format_analyzer_output";
  options.print_header_info = true;
  options.print_layer_defs = true;
  options.export_header_info = false;
  options.export_thumbnails = false;
  options.export_layer_defs = false;
  options.export_layer_masks = false;

  bool print_usage = false;

  for (int i = 1; i < argc; ++i) {
    if (std::strcmp(argv[i], "-o") == 0 || std::strcmp(argv[i], "--output-dir") == 0) {
      if (i + 1 < argc) {
        options.output_dir = argv[++i];
      } else {
        std::cerr << "Error: No output directory specified" << std::endl;
        print_usage = true;
      }
    } else if (std::strcmp(argv[i], "--no-header") == 0) {
      options.print_header_info = false;
    } else if (std::strcmp(argv[i], "--no-layer-defs") == 0) {
      options.print_layer_defs = false;
    } else if (std::strcmp(argv[i], "--export-header") == 0) {
      options.export_header_info = true;
    } else if (std::strcmp(argv[i], "--export-thumbnails") == 0) {
      options.export_thumbnails = true;
    } else if (std::strcmp(argv[i], "--export-layer-defs") == 0) {
      options.export_layer_defs = true;
    } else if (std::strcmp(argv[i], "--export-layer-masks") == 0) {
      options.export_layer_masks = true;
    } else if (argv[i][0] == '-') {
      std::cerr << "Error: Unknown argument " << argv[i] << std::endl;
      print_usage = true;
    } else {
      options.input_file = argv[i];
    }
  }

  if (options.input_file.empty()) {
    std::cerr << "Error: No input file specified" << std::endl;
    print_usage = true;
  }

  if (print_usage) {
    std::cerr << "Usage: " << argv[0] << " <input_file> [-o <output_dir>]" << std::endl;
    std::cerr << "Options:" << std::endl;
    std::cerr << "  --no-header                    Do not print header information" << std::endl;
    std::cerr << "  --no-layer-defs                Do not print layer definitions" << std::endl;
    std::cerr << "  -o, --output-dir <output_dir>  Specify the output directory for exports" << std::endl;
    std::cerr << "  --export-header                Export header information to a file" << std::endl;
    std::cerr << "  --export-thumbnails            Export thumbnails to files" << std::endl;
    std::cerr << "  --export-layer-defs            Export layer definitions to a file" << std::endl;
    std::cerr << "  --export-layer-masks           Export layer masks to files" << std::endl;
    throw std::runtime_error("Error: Invalid arguments, please see usage");
  }

  return options;
}