#ifndef _TERMINAL_H_GUARD_
#define _TERMINAL_H_GUARD_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "libk.h"
#include "vga.h"

struct terminal {
    size_t rows;
    size_t cols;
    size_t pos;
    uint16_t *buf;
    uint8_t colour;
};

extern void init_term(struct terminal *t, uint16_t *buf, size_t rows, size_t cols);
extern void putcharxy_term(struct terminal *t, size_t x, size_t y, char c);
extern void putchar_term(struct terminal *t, char c);
extern void write_term(struct terminal *t, char *s, size_t size);
extern void writestr_term(struct terminal *t, char *s);
extern void setcolour_term(struct terminal *t, uint8_t colour);

#endif