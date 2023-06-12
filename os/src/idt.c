/*
 * HyperCube OS
 * (c) Sergej Schumilo, 2019 <sergej@schumilo.de> 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */ 

#include "system.h"
#include "libk.h"
#include "tty.h"

typedef struct {
	uint16_t base_low;
	uint16_t sel;
	uint8_t zero;
	uint8_t flags;
	uint16_t base_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
	uint16_t limit;
	uintptr_t base;
} __attribute__((packed)) idt_pointer_t;

static struct {
	idt_entry_t entries[256];
	idt_pointer_t pointer;
} idt __attribute__((used));

#define ENTRY(X) (idt.entries[(X)])

typedef void (*idt_gate_t)(void);

extern void idt_load(uintptr_t);

void idt_set_gate(uint8_t num, idt_gate_t base, uint16_t sel, uint8_t flags) {
	ENTRY(num).base_low = ((uintptr_t)base & 0xFFFF);
	ENTRY(num).base_high = ((uintptr_t)base >> 16) & 0xFFFF;
	ENTRY(num).sel = sel;
	ENTRY(num).zero = 0;
	ENTRY(num).flags = flags | 0x60;
}

void idt_install(void) {
	idt_pointer_t * idtp = &idt.pointer;

	idtp->limit = sizeof(idt.entries)-1;
	idtp->base = (uintptr_t)&ENTRY(0);
	memset(&ENTRY(0), 0, sizeof(idt.entries));

	idt_load((uintptr_t)idtp);
}