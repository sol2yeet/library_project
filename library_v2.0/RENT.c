#include "RENT.h"
#include "STD.h"
#include <sys/stat.h>
#define MAX_LENGTH 256
#define ERROR_NOT_FOUND -1

/* 도서 대여 */
void rent_BOOK()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();

  FILE *r_fp = fopen(RENT_FILE_NAME, "a");
  // FILE *b_fp = fopen(BOOK_FILE_NAME, "a");

  if (r_fp == NULL)
  {
    printf("%s 파일열기 실패\n", RENT_FILE_NAME);
  }
  else
  {
    int book_num1, mem_phon; // 핸드폰 번호로 검색

    printf("도서 대출 가능 권수 : %d\n", pStd_ptr->b_idx);
    for (int i = 0; i < pStd_ptr->b_idx; i++)
    {
      printf("도서번호: %d, 제목: %s, 저자: %s, 장르: %s \r\n",
             pStd_ptr->BOOK_in[i].book_num,
             pStd_ptr->BOOK_in[i].title,
             pStd_ptr->BOOK_in[i].auth,
             pStd_ptr->BOOK_in[i].genre);
    }
    printf("대여할 도서의 번호를 입력해 주세요: ");
    scanf("%d", &book_num1); // 1. 도서번호 저장
    printf("\n");

    // FIXME : 회원정보 불러오기
    printf("등록 회원 수 : %d\n", pStd_ptr->h_idx);
    for (int j = 0; j < pStd_ptr->h_idx; j++)
    {
      printf("%s, %s, %s\r\n",
             pStd_ptr->MEM_in[j].name,
             pStd_ptr->MEM_in[j].phone,
             pStd_ptr->MEM_in[j].gene);
    }

    printf("대여할 회원의 핸드폰 번호 뒷자리를 입력해 주세요: ");
    scanf("%d", &mem_phon); // 2. 회원 뒷번호 저장
    printf("\n");

    pStd_ptr->RE[pStd_ptr->r_idx].rent_id = pStd_ptr->r_idx; // 대여번호

    pStd_ptr->RE[pStd_ptr->r_idx].book_num1 = pStd_ptr->BOOK_in[book_num1].book_num; // 번호등록

    pStd_ptr->RE[pStd_ptr->r_idx].mem_phon = mem_phon; // 회원번호
                                                       // timer = (time_t)time(NULL); // 대여일자

    // pStd_ptr->RE[pStd_ptr->r_idx].rent_date = timer;
    // pStd_ptr->RE[pStd_ptr->r_idx].due_date = (timer + 259200);      // 대여일 3일

    pStd_ptr->RE[pStd_ptr->r_idx].b_sta = 0; //  0: 대여중
    pStd_ptr->BOOK_in[book_num1].b_sta = 0;  //  0: 대여중

    t = localtime(&timer);
    printf("회원번호 %d 님, 대여 완료되었습니다. \n 처리일시: %d 년 %d월 %d일\n", pStd_ptr->RE[pStd_ptr->r_idx].mem_phon, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);

    fprintf(r_fp, "%d, %d, %d, %d\n", pStd_ptr->RE[pStd_ptr->r_idx].rent_id, pStd_ptr->RE[pStd_ptr->r_idx].book_num1, pStd_ptr->RE[pStd_ptr->r_idx].mem_phon, pStd_ptr->RE[pStd_ptr->r_idx].b_sta);
    pStd_ptr->r_idx++;

    fclose(r_fp);
  }
}

/*도서 반납 */
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
    int re_num1;
    int sec;
    int late_day;

    for (int j = 0; j < pStd_ptr->r_idx; j++)
    {
      printf("대여번호 : %d/ 책번호 : %d/ 핸드폰번호 : %d/ [대출상태 : %d] ( 0:대여중/ 1:대여가능)\n",
             pStd_ptr->RE[j].rent_id,
             pStd_ptr->RE[j].book_num1,
             pStd_ptr->RE[j].mem_phon,
             pStd_ptr->RE[j].b_sta);
    }
    printf("반납할 도서의 대여번호를 입력해 주세요: ");
    scanf("%d", &re_num1);

    printf("\n");

    pStd_ptr->RRE[pStd_ptr->rr_idx].rent_id = pStd_ptr->rr_idx; // 반납번호

    pStd_ptr->RRE[pStd_ptr->rr_idx].book_num1 = pStd_ptr->RE[re_num1].book_num1;

    pStd_ptr->RRE[re_num1].b_sta = 1;
    pStd_ptr->RRE[pStd_ptr->rr_idx].b_sta = 1;

    //    pStd_ptr->RRE[pStd_ptr->rr_idx].retu_date = tr = time(NULL); // 반납일자

    // 연체된 경우
    if (pStd_ptr->RRE[pStd_ptr->rr_idx].retu_date > pStd_ptr->RE[re_num1].due_date)
    {
      sec = pStd_ptr->RRE[pStd_ptr->rr_idx].retu_date - pStd_ptr->RE[re_num1].due_date;
      late_day = ((sec / 86400) + 1); // sec -> day
      printf("연체된 책입니다. 연체일수는 %d 일 입니다.", late_day);
    }
    printf("\n");

    printf("책 반납이 완료되었습니다.\n");
    fprintf(rr_fp, "\n %d, %d, %d ", pStd_ptr->RRE[pStd_ptr->rr_idx].rent_id, pStd_ptr->RRE[pStd_ptr->rr_idx].book_num1, pStd_ptr->RRE[pStd_ptr->rr_idx].b_sta);
    pStd_ptr->rr_idx++;
    fclose(rr_fp);
  }
}

void rent_list()
{

  STD_Mib *pStd_ptr = GET_STD_PTR();
  printf(" 대여 목록: \n");
  for (int i = 0; i < pStd_ptr->r_idx; i++)
  {
    if (pStd_ptr->RE[i].b_sta == 0)
    {
      printf("대여번호: %d 도서번호: %d 회원번호: %d [대출상태 : %d] ( 0:대여중/ 1:대여가능)\n", pStd_ptr->RE[pStd_ptr->r_idx].rent_id, pStd_ptr->RE[pStd_ptr->r_idx].book_num1, pStd_ptr->RE[pStd_ptr->r_idx].mem_phon, pStd_ptr->RE[pStd_ptr->r_idx].b_sta);
    }
  }
  printf("\n");

  printf("반납 목록: \n");
  for (int j = 0; j < pStd_ptr->rr_idx; j++)
  {
    if (pStd_ptr->RRE[j].b_sta == 1)
    {
      printf("반납번호: %d 도서번호: %d 회원번호: %d [대출상태 : %d] ( 0:대여중/ 1:대여가능)\n", pStd_ptr->RRE[pStd_ptr->rr_idx].rent_id, pStd_ptr->RRE[pStd_ptr->rr_idx].book_num1, pStd_ptr->RRE[pStd_ptr->rr_idx].mem_phon, pStd_ptr->RRE[pStd_ptr->rr_idx].b_sta);
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
        case 1: // 대여번호
          pStd_ptr->RE[pStd_ptr->r_idx].rent_id = atoi(ptr);
          break;
        case 2: // 도서번호
          pStd_ptr->RE[pStd_ptr->r_idx].book_num1 = atoi(ptr);
          break;
        case 3: // 대여회원의 폰번호
          pStd_ptr->RE[pStd_ptr->r_idx].mem_phon = atoi(ptr);
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
        case 1: // 대여번호
          pStd_ptr->RRE[pStd_ptr->rr_idx].rent_id = atoi(ptr);
          break;
        case 2: // 도서번호
          pStd_ptr->RRE[pStd_ptr->rr_idx].book_num1 = atoi(ptr);
          break;
        case 3: // 대여회원 폰번호
          pStd_ptr->RRE[pStd_ptr->rr_idx].mem_phon = atoi(ptr);
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
