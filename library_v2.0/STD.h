#ifndef _STD_H_
#define _STD_H_
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

/*--------------------------Variation-----------------------------*/

#define PROG_RUN 1
#define PROG_EXIT 0

typedef struct BOOK
{
  char title[30];
  char auth[30];
  char publ[30];
  char genre[10];
  int book_num;
  int b_sta; // 0: 대여, 1:반납
} BOOK;

typedef struct MEM
{
  char name[10];
  char gene[10];
  char phone[30];
} MEM;

typedef struct RENT
{
} RENT;

typedef struct STD_MIB
{
  // 각 기능별 인덱스(순서)
  int b_idx;
  int h_idx;
  int r_idx;
  // 기능 반복용 변수
  int rel;
  // 기능 선택용 변수
  int F_A;
  int F_B;
  BOOK BOOK_in[100];
  MEM MEM_in[100];

} STD_Mib;

/*---------------------------Function-----------------------------*/

/*
printf('1. 도서 검색 \n');
printf('2. 도서 추가 \n');
printf('3. 도서 삭제 \n');
printf('4. 나가기 \n');
*/
int BOOK_SW(int F_B);
int MEM_SW(int F_B);
void STD_INIT(void);
STD_Mib *GET_STD_PTR(void);

#endif /*_STD_H_*/