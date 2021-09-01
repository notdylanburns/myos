#include "terminal.h"

static inline size_t xy(struct terminal *t, size_t x, size_t y) {
    return x + t->cols * y;
}

static inline void nl_check(struct terminal *t) {
    if (t->pos > (t->rows * t->cols)) {
        for (size_t i = 1; i < t->rows; i++)
            memcpy(t->buf + (i - 1) * t->cols, t->buf + i * t->cols, sizeof(uint16_t) * t->cols);

        const uint16_t empty = vga_entry(' ', t->colour);
        for (size_t i = 0; i < t->cols; i++) {
            t->buf[xy(t, i, t->rows - 1)] = empty;
        }

        t->pos = t->cols * (t->rows - 1);
    }
}

void init_term(struct terminal *t, uint16_t *buf, size_t cols, size_t rows) {
    t->buf = buf;
    t->rows = rows;
    t->cols = cols;
    t->pos = 0ul;
    t->colour = vga_colour(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    const uint16_t empty = vga_entry(' ', t->colour);
    for (size_t x = 0; x < t->cols; x++)
        for (size_t y = 0; y < t->cols; y++)
            t->buf[xy(t, x, y)] = empty;
}

void putcharxy_term(struct terminal *t, size_t x, size_t y, char c) {
    switch (c) {
        case '\n':
            t->pos = t->cols * (t->pos / t->cols + 1);
            break;

        default:
            t->buf[xy(t, x, y)] = vga_entry(c, t->colour);
    }
    nl_check(t);
}

void putchar_term(struct terminal *t, char c) {
    switch (c) {
        case '\n':
            t->pos = t->cols * (t->pos / t->cols + 1);
            break;

        default:
            t->buf[t->pos++] = vga_entry(c, t->colour);
    }
    nl_check(t);
}

void write_term(struct terminal *t, char *s, size_t size) {
    for (size_t i = 0; i < size; i++)
        putchar_term(t, s[i]);
}

void writestr_term(struct terminal *t, char *s) {
    write_term(t, s, strlen(s));
}

void setcolour_term(struct terminal *t, uint8_t colour) {
    t->colour = colour;
}