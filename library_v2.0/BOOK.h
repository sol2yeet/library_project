#ifndef _BOOK_H_
#define _BOOK_H_

#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOK_FILE_NAME "BOOK.txt"
#define MAX_BOOK_NUM 100
#define MAX_BOOK_TITLE 255

typedef enum book
{
  ELEM_TYPE_TITLE,
  ELEM_TYPE_AUTH,
  ELEM_TYPE_GENRE,
  ELEM_TYPE_PUBL
} book;

void search_BOOK();
void add_BOOK();
void input_BOOK();
void delete_BOOK();
void Book_list(char *file);
int Get_bookfile_line(char *pfile_data, size_t file_size, char type, char *find_string);
void Delete_book_file_line(int file, char *pfile_data, size_t file_size, int line_cnt);

#endif /*_BOOK_H_ */
