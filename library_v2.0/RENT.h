#ifndef _RENT_H_
#define _RENT_H_

#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rent_BOOK();
void return_BOOK();
void input_RENT();
void input_RETURN();
void Set_bookfile_rent_stat(char *pfile_data, size_t file_size, int line_cnt, char rent_stat);
void Set_bookfile_return_stat(char *pfile_data, size_t file_size, int line_cnt, char rent_stat);

#endif /*_RENT_H_*/