#include <filesystem>
#include <fstream>
#include <iostream>

#include "goo_defs.hpp"

static void print_goo_header(std::ostream &ostream, const goo::header_info &header) {
  ostream << "Header:\n";
  ostream << "  Version: " << std::string(header.version, sizeof(header.version)) << std::endl;
  ostream << "  Magic Tag: ";
  ostream << std::hex << std::setw(2) << std::setfill('0');
  for (auto &tag : header.magic_tag)
    ostream << (int)tag;
  ostream << std::dec << std::setw(0) << std::setfill(' ') << "\n";
  ostream << "  Software Info: " << std::string(header.software_info, sizeof(header.software_info)) << std::endl;
  ostream << "  Software Version: " << std::string(header.software_version, sizeof(header.software_version)) << std::endl;
  ostream << "  File Time: " << std::string(header.file_time, sizeof(header.file_time)) << std::endl;
  ostream << "  Printer Name: " << std::string(header.printer_name, sizeof(header.printer_name)) << std::endl;
  ostream << "  Printer Type: " << std::string(header.printer_type, sizeof(header.printer_type)) << std::endl;
  ostream << "  Resin Profile Name: " << std::string(header.resin_profile_name, sizeof(header.resin_profile_name)) << std::endl;
  ostream << "  AA Level: " << header.aa_level << std::endl;
  ostream << "  Grey Level: " << header.grey_level << std::endl;
  ostream << "  Blur Level: " << header.blur_level << std::endl;
  ostream << "  Total Layers: " << header.total_layers << std::endl;
  ostream << "  X Resolution: " << header.x_resolution << std::endl;
  ostream << "  Y Resolution: " << header.y_resolution << std::endl;
  ostream << "  X Mirror: " << header.x_mirror << std::endl;
  ostream << "  Y Mirror: " << header.y_mirror << std::endl;
  ostream << "  X Platform Size (mm): " << header.x_platform_size_mm << std::endl;
  ostream << "  Y Platform Size (mm): " << header.y_platform_size_mm << std::endl;
  ostream << "  Z Platform Size (mm): " << header.z_platform_size_mm << std::endl;
  ostream << "  Layer Thickness (mm): " << header.layer_thickness_mm << std::endl;
  ostream << "  Common Exposure Time (s): " << header.common_exposure_time_s << std::endl;
  ostream << "  Exposure Delivery Time Static: " << header.exposure_delivery_time_static << std::endl;
  ostream << "  Turn Off Time (s): " << header.turn_off_time_s << std::endl;
  ostream << "  Bottom Before Lift Time (s): " << header.bottom_before_lift_time_s << std::endl;
  ostream << "  Bottom After Lift Time (s): " << header.bottom_after_lift_time_s << std::endl;
  ostream << "  Bottom After Retract Time (s): " << header.bottom_after_retract_time_s << std::endl;
  ostream << "  Before Lift Time (s): " << header.before_lift_time_s << std::endl;
  ostream << "  After Lift Time (s): " << header.after_lift_time_s << std::endl;
  ostream << "  After Retract Time (s): " << header.after_retract_time_s << std::endl;
  ostream << "  Bottom Exposure Time (s): " << header.bottom_exposure_time_s << std::endl;
  ostream << "  Bottom Layers: " << header.bottom_layers << std::endl;
  ostream << "  Bottom Lift Distance (mm): " << header.bottom_lift_distance_mm << std::endl;
  ostream << "  Bottom Lift Speed (mm/min): " << header.bottom_lift_speed_mm_min << std::endl;
  ostream << "  Lift Distance (mm): " << header.lift_distance_mm << std::endl;
  ostream << "  Lift Speed (mm/min): " << header.lift_speed_mm_min << std::endl;
  ostream << "  Bottom Retract Distance (mm): " << header.bottom_retract_distance_mm << std::endl;
  ostream << "  Bottom Retract Speed (mm/min): " << header.bottom_retract_speed_mm_min << std::endl;
  ostream << "  Retract Distance (mm): " << header.retract_distance_mm << std::endl;
  ostream << "  Retract Speed (mm/min): " << header.retract_speed_mm_min << std::endl;
  ostream << "  Bottom Second Lift Distance (mm): " << header.bottom_second_lift_distance_mm << std::endl;
  ostream << "  Bottom Second Lift Speed (mm/min): " << header.bottom_second_lift_speed_mm_min << std::endl;
  ostream << "  Second Lift Distance (mm): " << header.second_lift_distance_mm << std::endl;
  ostream << "  Second Lift Speed (mm/min): " << header.second_lift_speed_mm_min << std::endl;
  ostream << "  Bottom Second Retract Distance (mm): " << header.bottom_second_retract_distance_mm << std::endl;
  ostream << "  Bottom Second Retract Speed (mm/min): " << header.bottom_second_retract_speed_mm_min << std::endl;
  ostream << "  Second Retract Distance (mm): " << header.second_retract_distance_mm << std::endl;
  ostream << "  Second Retract Speed (mm/min): " << header.second_retract_speed_mm_min << std::endl;
  ostream << "  Bottom Light PWM: " << header.bottom_light_pwm << std::endl;
  ostream << "  Light PWM: " << header.light_pwm << std::endl;
  ostream << "  Advance Mode Layer Definition: " << header.advance_mode_layer_definition << std::endl;
  ostream << "  Printing Time (s): " << header.printing_time_s << std::endl;
  ostream << "  Total Volume (mm^3): " << header.total_volume_mm3 << std::endl;
  ostream << "  Total Weight (g): " << header.total_weight_g << std::endl;
  ostream << "  Total Price: " << header.total_price << std::endl;
  ostream << "  Price Unit: " << std::string(header.price_unit, sizeof(header.price_unit)) << std::endl;
  ostream << "  Layer Content Offset: " << header.layer_content_offset << std::endl;
  ostream << "  Grayscale Level: " << header.grayscale_level << std::endl;
  ostream << "  Transition Layers: " << header.transition_layers << std::endl;
}

static void print_goo_layer(std::ostream &ostream, size_t n, const goo::layer_definition &layer) {
  ostream << "Layer " << n << ":\n";
  ostream << "  Pause at Layer: " << layer.pause_at_layer << std::endl;
  ostream << "  Pause Lift Distance (mm): " << layer.pause_lift_distance_mm << std::endl;
  ostream << "  Position (mm): " << layer.position_mm << std::endl;
  ostream << "  Exposure Time (s): " << layer.exposure_time_s << std::endl;
  ostream << "  Off Time (s): " << layer.off_time_s << std::endl;
  ostream << "  Before Lift Time (s): " << layer.before_lift_time_s << std::endl;
  ostream << "  After Lift Time (s): " << layer.after_lift_time_s << std::endl;
  ostream << "  After Retract Time (s): " << layer.after_retract_time_s << std::endl;
  ostream << "  Lift Distance (mm): " << layer.lift_distance_mm << std::endl;
  ostream << "  Lift Speed (mm/min): " << layer.lift_speed_mm_min << std::endl;
  ostream << "  Second Lift Distance (mm): " << layer.second_lift_distance_mm << std::endl;
  ostream << "  Second Lift Speed (mm/min): " << layer.second_lift_speed_mm_min << std::endl;
  ostream << "  Retract Distance (mm): " << layer.retract_distance_mm << std::endl;
  ostream << "  Retract Speed (mm/min): " << layer.retract_speed_mm_min << std::endl;
  ostream << "  Second Retract Distance (mm): " << layer.second_retract_distance_mm << std::endl;
  ostream << "  Second Retract Speed (mm/min): " << layer.second_retract_speed_mm_min << std::endl;
  ostream << "  Light PWM: " << layer.light_pwm << std::endl;
}

void goo::print_file(const goo_file &file, cli_options options) {
  if (options.print_header_info) {
    print_goo_header(std::cout, file.header);
  }

  if (options.print_layer_defs) {
    for (size_t i = 0; i < file.header.total_layers; ++i) {
      print_goo_layer(std::cout, i, *file.layer_defs[i]);
    }
  }

  if (options.export_header_info || options.export_thumbnails || options.export_layer_defs || options.export_layer_masks) {
    std::filesystem::create_directories(options.output_dir);

    if (options.export_header_info) {
      std::ofstream header_info_file(options.output_dir + "/header_info.txt");
      print_goo_header(header_info_file, file.header);
    }

    if (options.export_thumbnails) {
      std::ofstream small_preview_file(options.output_dir + "/small_preview.ppm");
      small_preview_file << "P6\n116 116\n255\n";
      rgb565_decode(small_preview_file, file.header.small_preview);

      std::ofstream big_preview_file(options.output_dir + "/big_preview.ppm");
      big_preview_file << "P6\n290 290\n255\n";
      rgb565_decode(big_preview_file, file.header.big_preview);
    }

    if (options.export_layer_defs) {
      std::ofstream layer_defs_file(options.output_dir + "/layer_defs.txt");
      for (size_t i = 0; i < file.header.total_layers; ++i) {
        print_goo_layer(layer_defs_file, i, *file.layer_defs[i]);
      }
    }

    if (options.export_layer_masks) {
      std::filesystem::create_directories(options.output_dir + "/layer_masks");
      for (size_t i = 0; i < file.header.total_layers; ++i) {
        std::ofstream layer_mask_file(options.output_dir + "/layer_masks/layer_" + std::to_string(i) + ".pgm");
        layer_mask_file << "P5\n"                                                       // PGM magic number
                        << file.header.x_resolution << " " << file.header.y_resolution  // Width and height
                        << "\n255\n";                                                   // Maximum value
        rle_decode(layer_mask_file, file.layer_masks[i]);
      }
    }
  }
}