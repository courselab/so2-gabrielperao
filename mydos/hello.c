/*
 *    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
 *    SPDX-FileCopyrightText: 2024 Gabriel Barbosa de Amorim Perão <gabrielperao@usp.br>
 *    SPDX-FileCopyrightText: 2024 Ramon Moreira Machado <ramon1@usp.br>
 *
 *    SPDX-License-Identifier: GPL-3.0-or-later
 */
#include "tydos.h"

int main() {
  char input[BUFFER_MAX_SIZE];
  puts("Qual seu nome?");
  gets(input);
  puts("Hello ");
  puts(input);
  puts("\n");
  return 0;
}
