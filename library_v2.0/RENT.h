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

void rent_BOOK();    // 대출
void return_BOOK();  // 반납
void input_RENT();   // 대여정보 입력
void input_RETURN(); // 반납정보 입력
void Set_bookfile_rent_stat(char *pfile_data, size_t file_size, int line_cnt, char rent_stat);

#endif /*_RENT_H_*/