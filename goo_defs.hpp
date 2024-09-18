#pragma once

#include <cstdint>
#include <ostream>
#include <string>

#include "utility.hpp"

namespace goo {

#if defined(__GNUC__) || defined(__clang__)
#  define PACKED_PRE
#  define PACKED_IN [[gnu::packed]]
#  define PACKED_POST
#elif defined(_MSC_VER)
#  define PACKED_PRE __pragma(pack(push, 1))
#  define PACKED_IN
#  define PACKED_POST __pragma(pack(pop))
#elif
#  error "Unknown compiler for structure packing"
#endif

  // NOTE: All members need to be converted to big endian
  PACKED_PRE;
  struct PACKED_IN header_info {
    char version[4];
    uint8_t magic_tag[8];
    char software_info[32];
    char software_version[24];
    char file_time[24]{};
    char printer_name[32]{};
    char printer_type[32]{};
    char resin_profile_name[32];
    uint16_t aa_level;
    uint16_t grey_level;
    uint16_t blur_level;
    uint16_t small_preview[116 * 116];
    uint8_t delimiter_1[2];
    uint16_t big_preview[290 * 290];
    uint8_t delimiter_2[2];
    uint32_t total_layers;
    uint16_t x_resolution;
    uint16_t y_resolution;
    uint8_t x_mirror;
    uint8_t y_mirror;
    float x_platform_size_mm;
    float y_platform_size_mm;
    float z_platform_size_mm;
    float layer_thickness_mm;
    float common_exposure_time_s;
    bool exposure_delivery_time_static;
    float turn_off_time_s;
    float bottom_before_lift_time_s;
    float bottom_after_lift_time_s;
    float bottom_after_retract_time_s;
    float before_lift_time_s;
    float after_lift_time_s;
    float after_retract_time_s;
    float bottom_exposure_time_s;
    uint32_t bottom_layers;
    float bottom_lift_distance_mm;
    float bottom_lift_speed_mm_min;
    float lift_distance_mm;
    float lift_speed_mm_min;
    float bottom_retract_distance_mm;
    float bottom_retract_speed_mm_min;
    float retract_distance_mm;
    float retract_speed_mm_min;
    float bottom_second_lift_distance_mm;
    float bottom_second_lift_speed_mm_min;
    float second_lift_distance_mm;
    float second_lift_speed_mm_min;
    float bottom_second_retract_distance_mm;
    float bottom_second_retract_speed_mm_min;
    float second_retract_distance_mm;
    float second_retract_speed_mm_min;
    uint16_t bottom_light_pwm;
    uint16_t light_pwm;
    bool advance_mode_layer_definition;
    uint32_t printing_time_s;
    float total_volume_mm3;
    float total_weight_g;
    float total_price;
    char price_unit[8];
    uint32_t layer_content_offset;
    bool grayscale_level;
    uint16_t transition_layers;
  };
  PACKED_POST;
  static_assert(sizeof(header_info) == 195477, "struct is not packed");

  // NOTE: All members need to be converted to big endian
  PACKED_PRE;
  struct PACKED_IN layer_definition {
    uint8_t reserved;
    bool pause_at_layer;
    float pause_lift_distance_mm;
    float position_mm;
    float exposure_time_s;
    float off_time_s;
    float before_lift_time_s;
    float after_lift_time_s;
    float after_retract_time_s;
    float lift_distance_mm;
    float lift_speed_mm_min;
    float second_lift_distance_mm;
    float second_lift_speed_mm_min;
    float retract_distance_mm;
    float retract_speed_mm_min;
    float second_retract_distance_mm;
    float second_retract_speed_mm_min;
    uint16_t light_pwm;
    uint8_t delimiter[2];
  };
  PACKED_POST;
  static_assert(sizeof(layer_definition) == 66, "struct is not packed");

#undef PACKED_PRE
#undef PACKED_IN
#undef PACKED_POST

  struct goo_file {
    header_info& header;
    util::dynamic_array<layer_definition*> layer_defs;
    util::dynamic_array<util::span<uint8_t>> layer_masks;
  };

  struct cli_options {
    std::string input_file{};
    std::string output_dir{};
    bool print_header_info{};
    bool print_layer_defs{};
    bool export_header_info{};
    bool export_thumbnails{};
    bool export_layer_defs{};
    bool export_layer_masks{};
  };

  cli_options parse_cli(int argc, char* argv[]);

  util::dynamic_array<uint8_t> read_file(std::string filename);
  goo_file unpack_file(util::span<uint8_t> data);
  void print_file(const goo_file& file, cli_options options);

  void rgb565_decode(std::ostream& ostream, util::span<const uint16_t> image);
  void rle_decode(std::ostream& ostream, util::span<const uint8_t> mask);
}  // namespace goo