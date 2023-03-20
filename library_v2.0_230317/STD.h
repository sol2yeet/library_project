#ifndef _STD_H_
#define _STD_H_
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>

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
  int rent_id;         // 대여번호
  int book_num1;       // 도서 번호()
  char book_title[30]; // 도서제목
  int mem_phon;        // 회원 핸드폰 번호

  int rent_date; // 대여일자
  int due_date;  // 반납예정일자
  int retu_date; // 반납일자
  int b_sta;     // 0: 대여, 1:반납
} RENT;


typedef struct _BOOK_FILE_INFO_
{
  char use;
  BOOK book_info; 

}BOOK_FILE_INFO;


typedef struct STD_MIB
{

  BOOK_FILE_INFO book_info[100];


  
  // 각 기능별 인덱스(순서)
  int b_idx;  // 책 번호
  int h_idx;  // 회원번호
  int r_idx;  // 대여번호
  int rr_idx; // 반납번호
  // 기능 반복용 변수
  int rel;
  // 기능 선택용 변수
  int F_A;
  int F_B;
  BOOK BOOK_in[100];
  MEM MEM_in[100];
  RENT RE[100];  // 대여
  RENT RRE[100]; // 반납

} STD_Mib;

time_t *timer;
struct tm *tr;
struct tm *t;

/*---------------------------Function-----------------------------*/

/*
printf('1. 도서 검색 \n');
printf('2. 도서 추가 \n');
printf('3. 도서 삭제 \n');
printf('4. 나가기 \n');
*/
int BOOK_SW(int F_B);
int MEM_SW(int F_B);
int RENT_SW(int F_B);
void STD_INIT(void);
STD_Mib *GET_STD_PTR(void);

#endif /*_STD_H_*/