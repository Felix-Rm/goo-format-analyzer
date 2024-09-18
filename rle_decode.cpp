#include <numeric>
#include <stdexcept>

#include "goo_defs.hpp"

enum class type_tag : uint8_t {
  VALUE_00 = 0b00,
  VALUE_GRAYSCALE = 0b01,
  VALUE_DIFF = 0b10,
  VALUE_FF = 0b11
};

enum class length_tag : uint8_t {
  RUN_LENGTH_4BIT = 0b00,
  RUN_LENGTH_12BIT = 0b01,
  RUN_LENGTH_20BIT = 0b10,
  RUN_LENGTH_28BIT = 0b11,
};

struct chunk_header {
  // NOTE: bit field layout is reversed
  uint8_t length : 4;
  uint8_t length_tag : 2;
  uint8_t type_tag : 2;
};
static_assert(sizeof(chunk_header) == 1, "struct is not packed");

void goo::rle_decode(std::ostream &ostream, util::span<const uint8_t> mask) {
  uint8_t magic = mask[0];
  uint8_t checksum = mask[mask.size() - 1];
  mask = mask.subspan(1, mask.size() - 2);

  if (magic != 0x55) {
    throw std::runtime_error("Error: Invalid magic in layer mask");
  }

  uint8_t mask_checksum = ~std::reduce(mask.begin(), mask.end(), 0, std::plus<uint8_t>{});
  if (checksum != mask_checksum) {
    throw std::runtime_error("Error: Invalid checksum in layer mask");
  }

  while (mask.size()) {
    auto header = *reinterpret_cast<const chunk_header *>(mask.data());
    mask = mask.subspan(sizeof(chunk_header));

    auto repeat_value = [&]() -> uint8_t {
      type_tag header_type_tag = static_cast<type_tag>(header.type_tag);
      if (header_type_tag == type_tag::VALUE_00) return 0x00;
      if (header_type_tag == type_tag::VALUE_FF) return 0xFF;
      if (header_type_tag == type_tag::VALUE_GRAYSCALE) {
        auto value = mask.front();
        mask = mask.subspan(1);
        return value;
      };
      throw std::runtime_error("Error: Invalid or unsupported type tag in layer mask");
    }();

    auto repeat_length = [&]() -> size_t {
      uint32_t length = 0;
      for (size_t i = 0; i < header.length_tag; ++i) {
        length <<= 8;
        length |= mask.front();
        mask = mask.subspan(1);
      }

      length <<= 4;
      length |= header.length;
      return length;
    }();

    for (size_t i = 0; i < repeat_length; ++i) {
      ostream.put(repeat_value);
    }
  }
}