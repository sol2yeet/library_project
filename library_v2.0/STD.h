#ifndef _STD_H_
#define _STD_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>

#define ERROR_NOT_FOUND -1
#define PROG_RUN 1
#define PROG_EXIT 0
#define _CRT_SECURE_NO_WARNINGS
#define TYPE_LEN 512
#define ASCII_LINEFEED 0x0A
#define FILE_LENGTH 0x100
#define ASCII_COMMA 0x2C
#define ASCII_LINEFEED 0x0A
#define ASCII_SPACE 0x20
#define RENT_STAT

/* Variation */

typedef struct BOOK
{
  char title[30];
  char auth[30];
  char genre[10];
  char publ[30];
  int b_sta; // 0: 대여, 1:반납
} BOOK;

typedef struct MEM
{
  char name[10];
  char phone[30];
  char gene[10];
} MEM;

typedef struct RENT
{
  int rent_id;
  char book_title[30];
  int mem_phon;
  int rent_date; // 대여일자
  int due_date;  // 반납예정일자
  int retu_date; // 반납일자
  int b_sta;     // 0: 대여, 1:반납
} RENT;

typedef struct _BOOK_FILE_INFO_
{
  char use;
  BOOK book_info;
} BOOK_FILE_INFO;

typedef struct STD_MIB
{
  BOOK_FILE_INFO book_info[100];
  // 각 기능별 인덱스
  int b_idx;  // 책 번호
  int h_idx;  // 회원번호
  int r_idx;  // 대여번호
  int rr_idx; // 반납번호
  int rel;
  int F_A;
  int F_B;
  BOOK BOOK_in[100];
  MEM MEM_in[100];
  RENT RE[100];
  RENT RRE[100];
} STD_Mib;

time_t *timer;
struct tm *tr;
struct tm *t;

/* Function */

int BOOK_SW(int F_B);
int MEM_SW(int F_B);
int RENT_SW(int F_B);
void STD_INIT(void);
STD_Mib *GET_STD_PTR(void);

#endif /*_STD_H_*/