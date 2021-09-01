#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vga.h"
#include "terminal.h"

#if defined(__linux__)
#error "Kernel must be compiled with a cross compiler"
#endif

#if !defined(__i386__)
#error "Kernel must be compiled with a ix86-elf compiler"
#endif

void kernel_main(void) {
	struct terminal t;
	init_term(&t, (uint16_t *)0xb8000, 80, 25);
	while (1)
		writestr_term(&t, "hello world");
}