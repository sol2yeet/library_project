#ifndef _STD_H_
#define _STD_H_
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

/*--------------------------Variation-----------------------------*/

typedef struct BOOK
{
  char title[30];
  char auth[30];
  char publ[30];
  char genre[10];
  int book_num;
  int b_sta; // 0: 대여, 1:반납
} BOOK;
BOOK BOOK_in[100];

typedef struct MEM
{
  char name[10];
  char gene[10];
  char phone[30];
} MEM;
MEM MEM_in[100];

typedef struct RENT
{
} RENT;

// 각 기능별 인덱스(순서)
int b_idx = 0;
int h_idx = 0;
int r_idx = 0;
// 기능 반복용 변수
int rel = 1;
// 기능 선택용 변수
int F_A, F_B;

/*---------------------------Function-----------------------------*/

void input_MEM();
void input_BOOK();
// void input_RENT();
// void input_RETURN();

int MEM_SW(int F_B);
int search_MEM();
void add_MEM();
void del_MEM();

int BOOK_SW(int F_B);
int search_BOOK();
void add_BOOK();
void del_BOOK();

/*
printf('1. 도서 검색 \n');
printf('2. 도서 추가 \n');
printf('3. 도서 삭제 \n');
printf('4. 나가기 \n');
*/

int BOOK_SW(int F_B)
{
  int i, j;
  int book;
  switch (F_B)
  {
  case 1:
    printf("도서관리 - 도서검색 \n");
    book = search_BOOK();
    if (book == -3)
    {
      printf("입력한 제목에 일치하는 책이 없습니다.\n");
    }
    else
    {
      printf("도서 정보 \n 제목: %s 장르: %s 작가: %s 출판사: %s", BOOK_in[b_idx].title, BOOK_in[b_idx].genre, BOOK_in[b_idx].auth, BOOK_in[b_idx].publ);
    }
    break;

  case 2:
    printf("도서관리 - 도서추가 \n");
    add_BOOK();
    break;

  case 3:
    printf("도서관리 - 도서삭제 \n");
    del_BOOK();
    break;

  case 4:
    printf("전체 책 목록 불러오기 \n");
    for (i = 0; i < b_idx; i++)
    {
      printf("도서 정보 \n 제목: %s 장르: %s 작가: %s 출판사: %s", BOOK_in[b_idx].title, BOOK_in[b_idx].genre, BOOK_in[b_idx].auth, BOOK_in[b_idx].publ);
    }
    printf("\n");
    printf("목록을 그만 보고 싶으면 1을 눌러주세요 : ");
    scanf("%d", &j);
    if (j == i)
    {
      break;
    }
  case 5:
    printf("뒤로가기\n ");
    break;

  default:
    printf("잘못된 숫자를 입력하셨습니다. \n\n");
    break;
  }
  return 0;
};

/*
printf('1. 회원 검색 \n');
printf('2. 회원 추가 \n');
printf('3. 회원 삭제 \n');
printf('4. 나가기 \n');
*/

int MEM_SW(int F_B)
{
  int i, j;
  int MEM;
  switch (F_B)
  {
  case 1:
    printf("회원관리 - 회원검색 \n");
    MEM = search_MEM();
    if (MEM == -2)
    {
      printf("입력한 정보에 일치하는 회원이 없습니다.\n");
    }
    else
    {
      printf("회원정보\n 이름: %s 핸드폰번호: %s 성별: %s\n", MEM_in[MEM].name, MEM_in[MEM].phone, MEM_in[MEM].gene);
    }
    break;

  case 2:
    printf("회원관리 - 회원 추가 \n");
    add_MEM();
    break;

  case 3:
    printf("회원관리 - 회원삭제 \n");
    del_MEM();
    break;

  case 4:
    printf("전체 회원 목록 불러오기 \n");
    for (i = 0; i < h_idx; i++)
    {
      printf("회원정보\n 이름: %s 핸드폰번호: %s 성별: %s\n", MEM_in[MEM].name, MEM_in[MEM].phone, MEM_in[MEM].gene);
    }
    printf("\n");
    printf("목록을 그만 보고 싶으면 1을 눌러주세요 : ");
    scanf("%d", &j);
    if (j == i)
    {
      break;
    }
  case 5:
    printf("뒤로가기\n ");
    break;

  default:
    printf("잘못된 숫자를 입력하셨습니다. \n\n");
    break;
  }
  return 0;
};

#endif /*_STD_H_*/