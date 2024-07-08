/*
 *    SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
 *    SPDX-FileCopyrightText: 2024 Gabriel Barbosa de Amorim Perão <gabrielperao@usp.br>
 *    SPDX-FileCopyrightText: 2024 Ramon Moreira Machado <ramon1@usp.br>
 *
 *    SPDX-License-Identifier: GPL-3.0-or-later
 */

/* This source file implements the kernel entry function 'kmain' called
   by the bootloader, and the command-line interpreter. Other kernel functions
   were implemented separately in another source file for legibility. */

#include "file_sys.h"  /* To load disk into memory and get fs header */
#include "bios1.h"		/* For kwrite() etc.            */
#include "bios2.h"		/* For kread() etc.             */
#include "kernel.h"		/* Essential kernel functions.  */
#include "kaux.h"		/* Auxiliary kernel functions.  */

/* Kernel's entry function. */

void kmain(void)
{
  int i, j;
  
  register_syscall_handler();	/* Register syscall handler at int 0x21.*/

  splash();			/* Uncessary spash screen.              */

  shell();			/* Invoke the command-line interpreter. */
  
  halt();			/* On exit, halt.                       */
  
}

/* Tiny Shell (command-line interpreter). */

char buffer[BUFF_SIZE];
int go_on = 1;

void shell()
{
  int i;
  clear();
  kwrite ("BatDOS 1.0\n");

  while (go_on)
    {

      /* Read the user input. 
	 Commands are single-word ASCII tokens with no blanks. */
      do
	{
	  kwrite(PROMPT);
	  kread (buffer);
	}
      while (!buffer[0]);

      /* Check for matching built-in commands */
      
      i=0;
      while (cmds[i].funct)
	{
	  if (!strcmp(buffer, cmds[i].name))
	    {
	      cmds[i].funct();
	      break;
	    }
	  i++;
	}

      /* If the user input does not match any built-in command name, just
	 ignore and read the next command. If we were to execute external
	 programs, on the other hand, this is where we would search for a 
	 corresponding file with a matching name in the storage device, 
	 load it and transfer it the execution. Left as exercise. */
      
      if (!cmds[i].funct)
	kwrite ("Command not found\n");
    }
}


/* Array with built-in command names and respective function pointers.
   Function prototypes are in kernel.h. */

struct cmd_t cmds[] =
  {
    {"help",    f_help},     /* Print a help message.       */
    {"quit",    f_quit},     /* Exit BatDOS.                */
    {"exec",    f_exec},     /* Execute an example program. */
    {"list",    f_list},     /* Our command: List files.    */
    {0, 0}
  };


/* Build-in shell command: help. */

void f_help()
{
  kwrite ("...me, Obi-Wan, you're my only hope!\n\n");
  kwrite ("   But we can try also some commands:\n");
  kwrite ("      exec    (to execute an user program example\n");
  kwrite ("      list    (to list files\n");
  kwrite ("      quit    (to exit BatDOS)\n");
}

void f_quit()
{
  kwrite ("Program halted. Bye.");
  go_on = 0;
}

void f_exec() {
  char binary_file_name[BUFF_SIZE];

  kwrite("Input the name of the program you want to execute: ");
  kread(binary_file_name);

  struct file_sys_header_t* file_sys_header = get_file_sys_header();

  int coord_dir_sec = 1 + file_sys_header->num_boot_sectors;
  int sectors = (file_sys_header->num_entries * LEN_DIR / LEN_SECTOR) + 1;
  int offset = (file_sys_header->num_entries * LEN_DIR) - ((sectors - 1) * LEN_SECTOR);

  extern char _MEM_POOL_START;
  void* directory_section = (void*) &_MEM_POOL_START;

  load_disk(sectors, coord_dir_sec, directory_section);

  int coord_has_been_defined = 0;
  int coord_bin_sec;
  int i = 0;
  while (i < file_sys_header->num_entries)
  {
    char* file_name = directory_section + i * LEN_DIR;
    
    if (!strcmp(file_name, binary_file_name))
    {
      coord_bin_sec = sectors + coord_dir_sec + file_sys_header->max_file_size * i - 1;
      coord_has_been_defined = 1;
      break;
    }
    i++;
  }

  if (!coord_has_been_defined) {
    kwrite("Failed to find program\n");
    
    return;
  }

  void* program = (void*)(PROG_STARTADDR);
  void* program_sector_start = program - offset;
  int max_file_size = file_sys_header->max_file_size;
  
  load_disk(max_file_size, coord_bin_sec, program_sector_start);

  __asm__ volatile(
      "  call get_return_addr_into_ebx \n"
      "original_return_addr: \n"
      "  push %%ebx \n"
      "  jmp *%[progAddr] \n"
      "get_return_addr_into_ebx: \n"
      "  mov (%%esp), %%ebx \n"
      "  mov $prog_finish, %%ecx \n"
      "  sub $original_return_addr, %%ecx \n"
      "  add %%ecx, %%ebx \n"
      "  ret \n"
      "prog_finish:"

      ::[progAddr] "r"(program));
}

void f_list() {
  struct file_sys_header_t* file_sys_header = get_file_sys_header();

  int sectors = (file_sys_header->num_entries * LEN_DIR) / LEN_SECTOR;
  int sector_coord = file_sys_header->num_boot_sectors + 1;

  extern char _MEM_POOL_START;
  void* dir_sec = (void*) &_MEM_POOL_START;
  load_disk(sectors, sector_coord, dir_sec);

  int i = 0;
  for (; i < file_sys_header->num_entries; ++i)
  {
    char* f_name = i * LEN_DIR + dir_sec;
    if (!f_name[0]) continue;
    
    kwrite(f_name);
    kwrite("\n");
  }
}
