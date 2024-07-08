#    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
#    SPDX-FileCopyrightText: 2024 Gabriel Barbosa de Amorim Perão <gabrielperao@usp.br>
#    SPDX-FileCopyrightText: 2024 Ramon Moreira Machado <ramon1@usp.br>
#
#    SPDX-License-Identifier: GPL-3.0-or-later

	.code16gcc
	.global _start
	.text
	jmp _start
_start:
  call main
	ret
