/*
 *    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
 *    SPDX-FileCopyrightText: 2024 Gabriel B A Perão <gabrielperao@hotmail.com>
 *   
 *    SPDX-License-Identifier: GPL-3.0-or-later
 *
 *  This file is a derivative work from SYSeg (https://gitlab.com/monaco/syseg)
 *  and contains modifications carried out by the following author(s):
 *  Gabriel B A Perão <gabrielperao@hotmail.com>
 */

#include "bios.h"
#include "opt.h"

#define PROMPT "$ "    /* Prompt sign.      */
#define SIZE 20        /* Read buffer size. */

char buffer[SIZE];    /* Read buffer.      */

void vogal() {
  readln(buffer);
  for (int i = 0; i < SIZE; i++) {
    char c = buffer[i];
    if(c == '\0')
      return;

    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
      println("Tem vogal");
      return;
    }
  }
}

int main()
{
  clear();
  
  println  ("Boot Command 1.0");

  while (1)
    {
      print(PROMPT);    /* Show prompt.               */
      readln(buffer);    /* Read use input.            */

      if (buffer[0])    /* Execute built-in command.  */
      {
      if (!strcmp(buffer,"vogal"))
        vogal();
      else 
        println("Unkown command.");
      }
    }
  
  return 0;

}
