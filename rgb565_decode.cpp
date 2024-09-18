#include "goo_defs.hpp"

struct rgb565_pixel {
  // NOTE: bit field layout is reversed
  uint16_t b : 5;
  uint16_t g : 6;
  uint16_t r : 5;
};

static_assert(sizeof(rgb565_pixel) == 2, "struct is not packed");

void goo::rgb565_decode(std::ostream &ostream, util::span<const uint16_t> image) {
  for (auto pixel : image) {
    auto rgb = *reinterpret_cast<const rgb565_pixel *>(&pixel);
    ostream.put(rgb.r << 3);
    ostream.put(rgb.g << 2);
    ostream.put(rgb.b << 3);
  }
}