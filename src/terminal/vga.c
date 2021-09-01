#include "vga.h"

inline uint8_t vga_colour(enum vga_colour fg, enum vga_colour bg) {
    return (uint8_t)(bg << 4) | (uint8_t)fg;
}

inline uint16_t vga_entry(char c, uint8_t colour) {
    return (uint16_t)(colour << 8) | (uint16_t)c;
}