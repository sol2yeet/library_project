#include "RENT.h"
#include "STD.h"
#include <sys/stat.h>
#include <time.h>
#define MAX_LENGTH 256
#define ERROR_NOT_FOUND -1

void return_BOOK()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  FILE *rr_fp = fopen(RENT_FILE_NAME, "a");
  if (rr_fp == NULL)
  {
    printf("%s 파일열기 실패\n", RENT_FILE_NAME);
  }
  else
  {
    int re_num1; // book_num1 (매개변수)- 핸드폰 번호로 접근
    int sec;
    int late_day;

    for (int j = 0; j < pStd_ptr->r_idx; j++)
    {
      printf("대여번호 : %d/ 책번호 : %d/ 핸드폰번호 : %d/ 책상태 : [%d]\n",
             pStd_ptr->RE[pStd_ptr->r_idx].id,
             pStd_ptr->RE[pStd_ptr->r_idx].book_num1,
             pStd_ptr->RE[pStd_ptr->r_idx].hum_phon,
             pStd_ptr->RE[pStd_ptr->r_idx].b_sta);
    }
    printf("반납할 도서의 대여번호를 입력해 주세요: ");
    scanf("%d", &re_num1);

    printf("\n");

    pStd_ptr->RRE[pStd_ptr->rr_idx].id = pStd_ptr->rr_idx; // 반납번호

    pStd_ptr->RRE[pStd_ptr->rr_idx].book_num1 = pStd_ptr->RRE[re_num1].book_num1; // 번호등록

    pStd_ptr->RRE[re_num1].b_sta = 1;
    pStd_ptr->RRE[pStd_ptr->rr_idx].b_sta = 1;
    pStd_ptr->RRE[pStd_ptr->rr_idx].retu_date = tr = time(NULL); // 반납일자

    if (pStd_ptr->RRE[pStd_ptr->rr_idx].retu_date > pStd_ptr->RE[re_num1].due_date)
    { // 반납 일정 어긴 경우
      sec = pStd_ptr->RRE[pStd_ptr->rr_idx].retu_date - pStd_ptr->RRE[re_num1].due_date;
      late_day = ((sec / 86400) + 1); // 초-> 일 단위로 계산
      printf('연체된 책입니다. (연체일수 : %d)\n', late_day);
    }

    printf('책 반납이 완료되었습니다.\n');
    fprintf(rr_fp, "\n%d, %d, %d, %d ", pStd_ptr->RRE[pStd_ptr->rr_idx].id, pStd_ptr->RRE[pStd_ptr->rr_idx].book_num1, pStd_ptr->RRE[pStd_ptr->rr_idx].b_sta);
    pStd_ptr->rr_idx++;
    fclose(rr_fp);
  }
}

void rent_BOOK()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  FILE *r_fp = fopen(RENT_FILE_NAME, "a");
  if (r_fp == NULL)
  {
    printf("%s 파일열기 실패\n", RENT_FILE_NAME);
  }
  else
  {
    time_t timer;
    // struct tm* t;

    int book_num1, hum_phon; // book_num1 (매개변수)- 핸드폰 번호로 접근
    int t1, t2, t3;

    for (int i = 0; i < pStd_ptr->b_idx; i++)
    {

      printf("%d, %s, %s, %s, %s, %d\r\n",
             pStd_ptr->BOOK_in[pStd_ptr->b_idx].book_num,
             pStd_ptr->BOOK_in[pStd_ptr->b_idx].title,
             pStd_ptr->BOOK_in[pStd_ptr->b_idx].auth,
             pStd_ptr->BOOK_in[pStd_ptr->b_idx].genre,
             pStd_ptr->BOOK_in[pStd_ptr->b_idx].publ

      );
    }
    printf("대여할 도서의 번호를 입력해 주세요: ");
    scanf("%d", &book_num1); // %s -> %d

    for (int j = 0; j < pStd_ptr->h_idx; j++)
    {
      printf("%s, %s, %s\r\n",
             pStd_ptr->MEM_in[j].name,
             pStd_ptr->MEM_in[j].phone,
             pStd_ptr->MEM_in[j].gene);
    }
    printf("회원 핸드폰 번호를 입력해 주세요: ");
    scanf("%d", &hum_phon);

    pStd_ptr->RE[pStd_ptr->r_idx].id = pStd_ptr->r_idx; // 대여번호

    pStd_ptr->RE[pStd_ptr->r_idx].book_num1 = pStd_ptr->BOOK_in[book_num1].book_num; // 번호등록
    pStd_ptr->RE[pStd_ptr->r_idx].hum_phon = hum_phon;                               // 회원번호
    pStd_ptr->RE[pStd_ptr->r_idx].rent_date = timer = time(NULL);                    // 대여일자
    pStd_ptr->RE[pStd_ptr->r_idx].due_date = timer + 259200;                         // 대여일 3일

    pStd_ptr->RE[pStd_ptr->r_idx].b_sta = 0; // 1: 반납완료 , 0: 대여중
    pStd_ptr->BOOK_in[book_num1].b_sta = 0;  // 1: 반납완료, 0: 대여중

    t = localtime(&timer);
    printf('%d %d %d >>> %d : %d : %d (대여되면 0으로 출력[%d])\n', pStd_ptr->RE[pStd_ptr->r_idx].id, pStd_ptr->RE[pStd_ptr->r_idx].book_num1, pStd_ptr->RE[pStd_ptr->r_idx].hum_phon, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, pStd_ptr->RE[pStd_ptr->r_idx].b_sta);

    fprinf(r_fp, "\n%d, %d, %d, %d", pStd_ptr->RE[pStd_ptr->r_idx].id, pStd_ptr->RE[pStd_ptr->r_idx].book_num1, pStd_ptr->RE[pStd_ptr->r_idx].hum_phon, pStd_ptr->RE[pStd_ptr->r_idx].b_sta);
    pStd_ptr->r_idx++;

    fclose(r_fp);
  }
}

void rent_tot()
{

  STD_Mib *pStd_ptr = GET_STD_PTR();
  printf('대여 목록: \n');
  for (int i = 0; i < pStd_ptr->r_idx; i++)
  {
    if (pStd_ptr->RE[i].b_sta == 0)
    {
      printf('대여상황:  대여번호: %d 도서번호: %d 회원번호: %d (0이면 대여중)->[%d]\n', pStd_ptr->RE[pStd_ptr->r_idx].id, pStd_ptr->RE[pStd_ptr->r_idx].book_num1, pStd_ptr->RE[pStd_ptr->r_idx].hum_phon, pStd_ptr->RE[pStd_ptr->r_idx].b_sta);
    }
  }
  printf('\n');

  printf('반납 목록: \n');
  for (int j = 0; j < pStd_ptr->rr_idx; j++)
  {
    if (pStd_ptr->RE[j].b_sta == 1)
    {
      printf('반납상황:  반납번호: %d 도서번호: %d 회원번호: %d (0이면 대여중)->[%d]\n', pStd_ptr->RRE[j].id, pStd_ptr->RRE[j].book_num1, pStd_ptr->RRE[j].b_sta);
    }
  }
}

void input_RENT()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  FILE *r_fp = fopen(RENT_FILE_NAME, "r");
  if (r_fp == NULL)
  {
    printf("%s 파일열기 실패\n", RENT_FILE_NAME);
  }
  else
  {
    char line[150];
    char *ptr;
    int word_cnt;

    // 회원파일 입력
    while (fscanf(r_fp, "%s", line) > 0)
    {
      word_cnt = 0;
      ptr = strtok(line, ",");
      while (ptr != NULL)
      {
        word_cnt++;

        switch (word_cnt)
        {
        case 1: // id
          pStd_ptr->RE[pStd_ptr->r_idx].id = atoi(ptr);
          break;
        case 2: // 빌려간 책번호
          pStd_ptr->RE[pStd_ptr->r_idx].book_num1 = atoi(ptr);
          break;
        case 3: // 대여한 사람의 폰번호
          pStd_ptr->RE[pStd_ptr->r_idx].hum_phon = atoi(ptr);
          break;
        case 4: // 대여 상태
          pStd_ptr->RE[pStd_ptr->r_idx].b_sta = atoi(ptr);
          break;
        }
        ptr = strtok(NULL, ",");
      }
      pStd_ptr->r_idx++;
    }
    fclose(r_fp);
  }
}

void input_RETURN()
{

  STD_Mib *pStd_ptr = GET_STD_PTR();
  FILE *rr_fp = fopen(RENT_FILE_NAME, "r");
  if (rr_fp == NULL)
  {
    printf("%s 파일열기 실패\n", RENT_FILE_NAME);
  }
  else
  {
    char line[150];
    char *ptr;
    int word_cnt;

    // 회원파일 입력
    while (fscanf(rr_fp, "%s", line) > 0)
    {
      word_cnt = 0;
      ptr = strtok(line, ",");
      while (ptr != NULL)
      {
        word_cnt++;

        switch (word_cnt)
        {
        case 1: // id
          pStd_ptr->RRE[pStd_ptr->rr_idx].id = atoi(ptr);
          break;
        case 2: // 빌려간 책번호
          pStd_ptr->RRE[pStd_ptr->rr_idx].book_num1 = atoi(ptr);
          break;
        case 3: // 대여한 사람의 폰번호
          pStd_ptr->RRE[pStd_ptr->rr_idx].hum_phon = atoi(ptr);
          break;
        case 4: // 대여 상태
          pStd_ptr->RRE[pStd_ptr->rr_idx].b_sta = atoi(ptr);
          break;
        }
        ptr = strtok(NULL, ",");
      }
      pStd_ptr->r_idx++;
    }
    fclose(rr_fp);
  }
}
