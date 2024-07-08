/*
 *    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
 *    SPDX-FileCopyrightText: 2024 Gabriel Barbosa de Amorim Perão <gabrielperao@usp.br>
 *    SPDX-FileCopyrightText: 2024 Ramon Moreira Machado <ramon1@usp.br>
 *
 *    SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "bios1.h"		/* Function load_kernel . */
#include "kernel.h"		/* Function kmain.        */

int boot()
{

  load_kernel();		/* Load the kernel from disk image.  */

  kmain();		        /* Call the kernel's entry function. */

  return 0;

}

