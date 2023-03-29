#ifndef _MEM_H_
#define _MEM_H_

#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_FILE_NAME "MEM.txt"

typedef enum member
{
  ELEM_TYPE_NAME,
  ELEM_TYPE_PHONE,
  ELEM_TYPE_GENE
} member;

int MEM_list();
void search_MEM();
void add_MEM();
void input_MEM();
void delete_MEM();

#endif /*_MEM_H_*/