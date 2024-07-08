/*
 *    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
 *    SPDX-FileCopyrightText: 2024 Gabriel Barbosa de Amorim Perão <gabrielperao@usp.br>
 *    SPDX-FileCopyrightText: 2024 Ramon Moreira Machado <ramon1@usp.br>
 *
 *    SPDX-License-Identifier: GPL-3.0-or-later
 */
#ifndef FILE_SYS_H
#define FILE_SYS_H

#include "kaux.h"

#define LEN_SECTOR 512
#define LEN_DIR 32
#define us unsigned short
#define uc unsigned char
#define ui unsigned int

struct file_sys_header_t {
  uc signature[4];
  us num_sectors;  
  us num_boot_sectors;
  us num_entries;
  us max_file_size;
  ui unused_space;
} __attribute__((packed));

struct file_sys_header_t* get_file_sys_header();

void load_disk(int sectors, int coord, void* target_address);

#endif
