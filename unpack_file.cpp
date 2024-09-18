#include <stdexcept>

#include "goo_defs.hpp"

template<typename T>
T hton(T value) {
  static_assert(std::is_trivially_copyable_v<T>, "Type must be trivially copyable");
  static_assert(sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8, "Type must be 1, 2, 4, or 8 bytes");
  auto* bytes = reinterpret_cast<uint8_t*>(&value);
  for (size_t i = 0; i < sizeof(T) / 2; ++i)
    std::swap(bytes[i], bytes[sizeof(T) - 1 - i]);
  return value;
}

// NOTE: This could be done without a macro in newer C++ versions
// For compatibility with C++17, we use a macro
// (References do not work because struct members are packed)
#define INPLACE_HTON(x) x = hton((x))
#define INPLACE_HTON_ARRAY(x)                                                                      \
  for (size_t hton_iterate_i = 0; hton_iterate_i < sizeof((x)) / sizeof((x)[0]); hton_iterate_i++) \
    (x)[hton_iterate_i] = INPLACE_HTON((x)[hton_iterate_i]);

goo::goo_file goo::unpack_file(util::span<uint8_t> data) {
  if (data.size() < sizeof(header_info)) {
    throw std::runtime_error("Error: File is too small");
  }

  auto& header = *reinterpret_cast<header_info*>(data.data());
  INPLACE_HTON_ARRAY(header.version);
  INPLACE_HTON_ARRAY(header.magic_tag);
  INPLACE_HTON_ARRAY(header.software_info);
  INPLACE_HTON_ARRAY(header.software_version);
  INPLACE_HTON_ARRAY(header.file_time);
  INPLACE_HTON_ARRAY(header.printer_name);
  INPLACE_HTON_ARRAY(header.printer_type);
  INPLACE_HTON_ARRAY(header.resin_profile_name);
  INPLACE_HTON(header.aa_level);
  INPLACE_HTON(header.grey_level);
  INPLACE_HTON(header.blur_level);
  INPLACE_HTON_ARRAY(header.small_preview);
  INPLACE_HTON_ARRAY(header.delimiter_1);
  INPLACE_HTON_ARRAY(header.big_preview);
  INPLACE_HTON_ARRAY(header.delimiter_2);
  INPLACE_HTON(header.total_layers);
  INPLACE_HTON(header.x_resolution);
  INPLACE_HTON(header.y_resolution);
  INPLACE_HTON(header.x_mirror);
  INPLACE_HTON(header.y_mirror);
  INPLACE_HTON(header.x_platform_size_mm);
  INPLACE_HTON(header.y_platform_size_mm);
  INPLACE_HTON(header.z_platform_size_mm);
  INPLACE_HTON(header.layer_thickness_mm);
  INPLACE_HTON(header.common_exposure_time_s);
  INPLACE_HTON(header.exposure_delivery_time_static);
  INPLACE_HTON(header.turn_off_time_s);
  INPLACE_HTON(header.bottom_before_lift_time_s);
  INPLACE_HTON(header.bottom_after_lift_time_s);
  INPLACE_HTON(header.bottom_after_retract_time_s);
  INPLACE_HTON(header.before_lift_time_s);
  INPLACE_HTON(header.after_lift_time_s);
  INPLACE_HTON(header.after_retract_time_s);
  INPLACE_HTON(header.bottom_exposure_time_s);
  INPLACE_HTON(header.bottom_layers);
  INPLACE_HTON(header.bottom_lift_distance_mm);
  INPLACE_HTON(header.bottom_lift_speed_mm_min);
  INPLACE_HTON(header.lift_distance_mm);
  INPLACE_HTON(header.lift_speed_mm_min);
  INPLACE_HTON(header.bottom_retract_distance_mm);
  INPLACE_HTON(header.bottom_retract_speed_mm_min);
  INPLACE_HTON(header.retract_distance_mm);
  INPLACE_HTON(header.retract_speed_mm_min);
  INPLACE_HTON(header.bottom_second_lift_distance_mm);
  INPLACE_HTON(header.bottom_second_lift_speed_mm_min);
  INPLACE_HTON(header.second_lift_distance_mm);
  INPLACE_HTON(header.second_lift_speed_mm_min);
  INPLACE_HTON(header.bottom_second_retract_distance_mm);
  INPLACE_HTON(header.bottom_second_retract_speed_mm_min);
  INPLACE_HTON(header.second_retract_distance_mm);
  INPLACE_HTON(header.second_retract_speed_mm_min);
  INPLACE_HTON(header.bottom_light_pwm);
  INPLACE_HTON(header.light_pwm);
  INPLACE_HTON(header.advance_mode_layer_definition);
  INPLACE_HTON(header.printing_time_s);
  INPLACE_HTON(header.total_volume_mm3);
  INPLACE_HTON(header.total_weight_g);
  INPLACE_HTON(header.total_price);
  INPLACE_HTON_ARRAY(header.price_unit);
  INPLACE_HTON(header.layer_content_offset);
  INPLACE_HTON(header.grayscale_level);
  INPLACE_HTON(header.transition_layers);

  if (data.size() < sizeof(header_info) + header.total_layers * sizeof(layer_definition)) {
    throw std::runtime_error("Error: File size does not match expected size");
  }

  goo_file file{header, {header.total_layers}, {header.total_layers}};
  size_t file_position = sizeof(header_info);

  for (size_t i = 0; i < file.layer_defs.size(); ++i) {
    auto* layer = reinterpret_cast<layer_definition*>(data.data() + file_position);
    file_position += sizeof(layer_definition);

    auto mask_length = *reinterpret_cast<uint32_t*>(data.data() + file_position);
    file_position += sizeof(uint32_t);
    INPLACE_HTON(mask_length);

    auto mask = util::span(data.data() + file_position, mask_length);
    file_position += mask_length;

    file_position += 2;  // Skip delimiter

    INPLACE_HTON(layer->reserved);
    INPLACE_HTON(layer->pause_at_layer);
    INPLACE_HTON(layer->pause_lift_distance_mm);
    INPLACE_HTON(layer->position_mm);
    INPLACE_HTON(layer->exposure_time_s);
    INPLACE_HTON(layer->off_time_s);
    INPLACE_HTON(layer->before_lift_time_s);
    INPLACE_HTON(layer->after_lift_time_s);
    INPLACE_HTON(layer->after_retract_time_s);
    INPLACE_HTON(layer->lift_distance_mm);
    INPLACE_HTON(layer->lift_speed_mm_min);
    INPLACE_HTON(layer->second_lift_distance_mm);
    INPLACE_HTON(layer->second_lift_speed_mm_min);
    INPLACE_HTON(layer->retract_distance_mm);
    INPLACE_HTON(layer->retract_speed_mm_min);
    INPLACE_HTON(layer->second_retract_distance_mm);
    INPLACE_HTON(layer->second_retract_speed_mm_min);
    INPLACE_HTON(layer->light_pwm);
    INPLACE_HTON_ARRAY(layer->delimiter);

    file.layer_defs[i] = layer;
    file.layer_masks[i] = mask;
  }

  return file;
}