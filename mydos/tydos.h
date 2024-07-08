/*
 *    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
 *    SPDX-FileCopyrightText: 2024 Gabriel Barbosa de Amorim Perão <gabrielperao@usp.br>
 *    SPDX-FileCopyrightText: 2024 Ramon Moreira Machado <ramon1@usp.br>
 *
 *    SPDX-License-Identifier: GPL-3.0-or-later
 */

/* Library libtydos.a should be statically linked against user programs meant
   for running on BatDOS. It provides some custom C functions that invoke system
   calls for trivial tasks.

   This is the header file that should be included in the user programs. */

#ifndef BATDOS_H
#define BATDOS_H

/* Syscall numbers. */

#define SYS_INVALID 0
#define SYS_EXIT    1
#define SYS_WRITE   2
#define SYS_READ    3
#define BUFFER_MAX_SIZE 10

void puts(const char* str);	/* Outputs 'str' on the screen. */
void gets(char* buffer);  /* Reads buffer */

#endif
