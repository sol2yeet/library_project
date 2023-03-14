#ifndef _BOOK_H_
#define _BOOK_H_

#include "STD.h"

/*
#도서관리
1. 도서검색
2. 도서추가 <도서명, 작가, 출판사, 분야, 도서코드>
3. 도서삭제
*/

int search_BOOK()
{

  int i;
  char title[30];
  printf("제목 : ");
  scanf("%s", title);

  for (i = 0; i < b_idx; i++)
  {
    if (strcmp(title, BOOK_in[i].title) == 0)
      return i; // strcmp(문자열1, 문자열2); 문자열 비교 함수
  }
  return -3; // 음수로 하여 겹치는 것 방지
}

// 파일에 저장
void add_BOOK()
{
  FILE *b_fp;
  b_fp = fopen("BOOK.txt", "a");

  if (b_fp == NULL)
  {
    printf("파일열기 실패\n");
  }
  else
  {
    printf("파일열기 성공\n");
  }

  // 구조체 배열 정보를 입력받음
  printf("도서번호 : ");
  scanf("%d", &BOOK_in[b_idx].book_num);
  printf("도서 제목 : ");
  scanf("%s", BOOK_in[b_idx].title);
  printf("장르 : ");
  scanf("%s", BOOK_in[b_idx].genre);
  printf("작가 : ");
  scanf("%s", BOOK_in[b_idx].auth);
  printf("출판사 : ");
  scanf("%s", BOOK_in[b_idx].publ);
  printf("도서를 입력합니다. (1 : 입력) : ");
  scanf("%d", &BOOK_in[b_idx].b_sta);
  BOOK_in[b_idx].b_sta = 1; // 도서있음(1) / 도서 없음(0)

  fprintf(b_fp, "%d\n, %d, %s, %s, %s, %s", BOOK_in[b_idx].b_sta // 책이 들어있는 것 표현
          ,
          BOOK_in[b_idx].book_num, BOOK_in[b_idx].title, BOOK_in[b_idx].auth, BOOK_in[b_idx].publ, BOOK_in[b_idx].genre);
  b_idx++; // 총 책 권수 증가 +1

  fclose(b_fp);

  // return 1;
}

void input_BOOK()
{
  FILE *b_fp;
  b_fp = fopen("BOOK.txt", "r");
  if (b_fp == NULL)
  {
    printf("파일열기 실패\n");
  }
  else
  {
    printf("파일열기 성공\n");
  }

  char line[150];
  char *ptr;
  int word_cnt;

  // BOOK 파일 입력
  while (fscanf(b_fp, "%s", line) > 0)
  {
    word_cnt = 0;
    // printf('%s\n', line);
    ptr = strtok(line, ",");
    while (ptr != NULL)
    {
      word_cnt++;
      switch (word_cnt) // 하나씩 증가하면서 한개씩 읽어서 표현
      {
      case 1:                                // int
        BOOK_in[b_idx].book_num = atoi(ptr); // 숫자로 바꿔주기
        break;

      case 2: // char title
        strcpy(BOOK_in[b_idx].title, ptr);
        break;

      case 3: // char genre
        strcpy(BOOK_in[b_idx].genre, ptr);
        break;

      case 4: // char auth
        strcpy(BOOK_in[b_idx].auth, ptr);
        break;

      case 5: // char publisher
        strcpy(BOOK_in[b_idx].publ, ptr);
        break;
      }
      ptr = strtok(NULL, ",");
    }
    b_idx++;
  }
  fclose(b_fp); // 파일 포인터 닫기
} // 책 정보 입력

void del_BOOK()
{ // 기존 삭제 기능 활용
  FILE *b_fp;
  b_fp = fopen("BOOK.txt", "w");
  if (b_fp == NULL)
  {
    printf("파일열기 실패\n");
  }
  else
  {
    printf("파일열기 성공\n");
  }

  // 구조체 배열에 정보를 입력받음
  printf("도서 제목 : ");
  scanf("%s", BOOK_in[b_idx].title);

  printf("장르 : ");
  scanf("%s", BOOK_in[b_idx].genre);

  printf("작가 : ");
  scanf("%s", BOOK_in[b_idx].auth);

  printf("출판사 : ");
  scanf("%s", BOOK_in[b_idx].publ);

  printf("도서 번호 : ");
  scanf("%d", &BOOK_in[b_idx].book_num);
  fprintf(b_fp, "\n%d, %s, %s, %s, %s", BOOK_in[b_idx].book_num, BOOK_in[b_idx].title, BOOK_in[b_idx].auth, BOOK_in[b_idx].publ, BOOK_in[b_idx].genre);
  fclose(b_fp);
}

#endif /*_BOOK_H_ */
