/*
 *    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
 *    SPDX-FileCopyrightText: 2024 Gabriel Barbosa de Amorim Perão <gabrielperao@usp.br>
 *    SPDX-FileCopyrightText: 2024 Ramon Moreira Machado <ramon1@usp.br>
 *
 *    SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "file_sys.h"
#include "kaux.h"

void load_disk(int sectors, int coord, void* target_address)
{
  int coord_head = (coord - 1) / 63;
  int coord_sector = (coord - 1) % 63 + 1;

  __asm__ volatile(
      "pusha \n"
      "mov boot_drive, %%dl \n"
      "mov $0x2, %%ah \n"
      "mov %[sectToRead], %%al \n"
      "mov $0x0, %%ch \n"
      "mov %[sectCoord], %%cl \n"
      "mov %[headCoord], %%dh \n"
      "mov %[targetAddr], %%bx \n"
      "int $0x13 \n"
      "popa \n" :: [headCoord] "g"(coord_head), [sectCoord] "g"(coord_sector), [sectToRead] "g"(sectors), [targetAddr] "g"(target_address));
}

struct file_sys_header_t *get_file_sys_header() { return (struct file_sys_header_t *) 0x7c00; }
