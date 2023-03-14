#include "BOOK.h"
#include "STD.h"
#include <sys/stat.h>
#define MAX_LENGTH 256
#define ERROR_NOT_FOUND -1

int sort_BOOK()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  FILE *b_fp = fopen("BOOK.txt", "rb");
  if (b_fp == NULL)
  {
    printf("파일열기 실패\n");
  }
  else
  {
    printf("=============================\n");
    printf("========== 도서 목록 =========\n");
    printf("=============================\n");

    struct stat sk;
    if (stat("BOOK.txt", &sk) == -1)
    {
      perror("stat");
      exit(EXIT_FAILURE);
    }

    char *file_contents = malloc(sk.st_size);

    int i = 1;
    while (fscanf(b_fp, "%[^\n] ", file_contents) != EOF)
    {
      printf("[%d] %s\n", i, file_contents);
      i++;
    }

    printf("================================\n");
    printf("\n");

    fclose(b_fp);
  }
}

int search_BOOK()
{
  int val = -3;
  STD_Mib *pStd_ptr = GET_STD_PTR();

  char title[30];
  printf("=============================\n");
  printf("======= 도서검색 페이지 =======\n");
  printf("=============================\n");
  printf("제목을 입력하세요 : ");
  scanf("%s", title);
  printf("\n");

  for (int i = 0; i < pStd_ptr->b_idx; i++)
  {
    if (strcmp(title, pStd_ptr->BOOK_in[i].title) == 0)
    {
      val = i;
      break; // strcmp(문자열1, 문자열2); 문자열 비교 함수
    }
  }
  printf("\n");
  return val; // multi return 자제..
}

void add_BOOK()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();

  FILE *b_fp;
  b_fp = fopen("BOOK.txt", "a");

  if (b_fp == NULL)
  {
    printf("파일열기 실패\n");
  }
  else
  {
    printf("=============================\n");
    printf("======= 도서추가 페이지 =======\n");
    printf("=============================\n");
    // 구조체 배열 정보를 입력받음
    printf("도서 번호 : ");
    scanf("%d", &pStd_ptr->BOOK_in[pStd_ptr->b_idx].book_num);
    printf("제목 : ");
    scanf("%s", pStd_ptr->BOOK_in[pStd_ptr->b_idx].title);
    printf("작가 : ");
    scanf("%s", pStd_ptr->BOOK_in[pStd_ptr->b_idx].auth);
    printf("장르 : ");
    scanf("%s", pStd_ptr->BOOK_in[pStd_ptr->b_idx].genre);
    printf("출판사 : ");
    scanf("%s", pStd_ptr->BOOK_in[pStd_ptr->b_idx].publ);
    printf("도서를 등록합니다. (1 : 입력) : ");
    scanf("%d", &pStd_ptr->BOOK_in[pStd_ptr->b_idx].b_sta);
    pStd_ptr->BOOK_in[pStd_ptr->b_idx].b_sta = 1; // 도서있음(1) / 도서 없음(0)

    pStd_ptr->b_idx++; // 총 책 권수 증가 +1
    fprintf(b_fp, "%d, %s, %s, %s, %s, %d",
            pStd_ptr->BOOK_in[pStd_ptr->b_idx].book_num, pStd_ptr->BOOK_in[pStd_ptr->b_idx].title, pStd_ptr->BOOK_in[pStd_ptr->b_idx].auth, pStd_ptr->BOOK_in[pStd_ptr->b_idx].genre, pStd_ptr->BOOK_in[pStd_ptr->b_idx].publ, pStd_ptr->BOOK_in[pStd_ptr->b_idx].b_sta // 도서있음(1) / 도서 없음(0)

    );
    printf("\n");
    printf("도서가 등록되었습니다.\n");
    printf("\n");

    fclose(b_fp);
  }

  // return 1;
}

void input_BOOK()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  FILE *b_fp;
  char line[150];
  char *ptr;
  int word_cnt;
  b_fp = fopen("BOOK.txt", "r");
  if (b_fp == NULL)
  {
    printf("파일열기 실패\n");
  }
  else
  {
    printf(" ");

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
        case 1:                                                    // int
          pStd_ptr->BOOK_in[pStd_ptr->b_idx].book_num = atoi(ptr); // 숫자로 바꿔주기
          break;

        case 2: // char title
          strcpy(pStd_ptr->BOOK_in[pStd_ptr->b_idx].title, ptr);
          break;

        case 3: // char auth
          strcpy(pStd_ptr->BOOK_in[pStd_ptr->b_idx].auth, ptr);
          break;

        case 4: // char genre
          strcpy(pStd_ptr->BOOK_in[pStd_ptr->b_idx].genre, ptr);
          break;

        case 5: // char publisher
          strcpy(pStd_ptr->BOOK_in[pStd_ptr->b_idx].publ, ptr);
          break;
        }
        ptr = strtok(NULL, ",");
      }
      pStd_ptr->b_idx++;
    }
    fclose(b_fp); // 파일 포인터 닫기
  }
} // 책 정보 입력

void delete_BOOK()
{ // 기존 삭제 기능 활용
  STD_Mib *pStd_ptr = GET_STD_PTR();
  FILE *b_fp;
  b_fp = fopen("BOOK.txt", "w");
  if (b_fp == NULL)
  {
    printf("파일열기 실패\n");
  }
  else
  {
    printf("=============================\n");
    printf("======= 도서삭제 페이지 =======\n");
    printf("=============================\n");
    printf("\n");
    printf("\n");
    printf("\n");

    // TODO
    /* 도서검색 -> 삭제하시겠습니까? -> 업데이트된 목록을 보여줌*/

    fclose(b_fp);
  }
}
