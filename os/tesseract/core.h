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

#pragma once 
#include <stdint.h>
#include "state.h"
#include "opcodes.h"
#include "decompiler.h"

#ifdef PAYLOAD
void run(hexa_op* instructions, uint32_t len, state_t* state_obj, opcode_bitmap_t opcode_bitmap);
#else
void run(hexa_op* instructions, uint32_t num, state_t* state_obj);
#endif