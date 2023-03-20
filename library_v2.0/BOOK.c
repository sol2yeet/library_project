#include "BOOK.h"
#include "STD.h"
#include <sys/stat.h>
#define MAX_LENGTH 256
#define ERROR_NOT_FOUND -1

int sort_BOOK()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  FILE *b_fp = fopen(BOOK_FILE_NAME, "rb");
  if (b_fp == NULL)
  {
    printf("%s 파일열기 실패\n", BOOK_FILE_NAME);
  }
  else
  {
    struct stat sk;
    char *file_contents;
    printf("=============================\n");
    printf("========== 도서 목록 =========\n");
    printf("=============================\n");

    if (stat(BOOK_FILE_NAME, &sk) == -1)
    {
      perror("stat");
      exit(EXIT_FAILURE);
    }
    file_contents = malloc(sk.st_size);

    int i = 1;
    while (fscanf(b_fp, "%[^\n] ", file_contents) != EOF)
    {
      printf("[%d] %s\n", i, file_contents);
      i++;
    }

    printf("================================\n");
    printf("\n");
    free(file_contents);
    fclose(b_fp);
  }
}

int search_BOOK()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  int val = -3;
  char title[30];
  printf("=============================\n");
  printf("======= 도서검색 페이지 =======\n");
  printf("=============================\n");
  printf("제목을 입력하세요 : ");
  scanf("%s", title);
  printf("\n");

  for (int i = 0; i < pStd_ptr->b_idx; i++)
  {
    printf("#%d %s/%s\n", i, title, pStd_ptr->BOOK_in[i].title);
    if (strcmp(title, pStd_ptr->BOOK_in[i].title) == 0)
    {
      val = i;
      break;
    }
  }
  printf("\n");
  return val;
}

void add_BOOK()
/*FIXME

1.도서번호는 순차적으로 등록 및 삭제되어야 한다.
  -> 도서 등록시 입력받는 번호는 순번이 아닌 삭제및대여기능을 수행하기위한 고유식별번호이다(사용법 고민)

2.출력시 등록된 도서의 정보와 전체 목록이 출력된다.
  -> sort_BOOK()실행
  */
{
  STD_Mib *pStd_ptr = GET_STD_PTR();

  FILE *b_fp;
  b_fp = fopen(BOOK_FILE_NAME, "a");

  if (b_fp == NULL)
  {
    printf("파일열기 실패\n");
  }
  else
  {
    printf("=============================\n");
    printf("======= 도서추가 페이지 =======\n");
    printf("=============================\n");
  }

  if (b_fp != NULL)
  {
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

    fprintf(b_fp, "%d, %s, %s, %s, %s, %d\r\n",
            pStd_ptr->BOOK_in[pStd_ptr->b_idx].book_num,
            pStd_ptr->BOOK_in[pStd_ptr->b_idx].title,
            pStd_ptr->BOOK_in[pStd_ptr->b_idx].auth,
            pStd_ptr->BOOK_in[pStd_ptr->b_idx].genre,
            pStd_ptr->BOOK_in[pStd_ptr->b_idx].publ,
            pStd_ptr->BOOK_in[pStd_ptr->b_idx].b_sta // 도서있음(1) / 도서 없음(0)
    );

    pStd_ptr->b_idx++;
    printf("\n");
    printf("도서가 등록되었습니다.\n");
    printf("\n");

    fclose(b_fp);
  }
}

void input_BOOK()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  FILE *b_fp;
  char line[150];
  char *ptr;
  int word_cnt = 0;
  int book_index = 0;
  b_fp = fopen(BOOK_FILE_NAME, "r");
  if (b_fp == NULL)
  {
    printf("파일열기 실패\n");
  }
  else
  {
    printf(" ");
    while (fscanf(b_fp, "%s", line) > 0)
    {
      if (word_cnt > 5)
      {
        word_cnt = 0;
        pStd_ptr->b_idx++;
      }

      // printf('%s\n', line);
      ptr = strtok(line, ",");
      //   while (ptr != NULL)
      {
        word_cnt++;

        switch (word_cnt)
        {
        case 1:
          pStd_ptr->BOOK_in[pStd_ptr->b_idx].book_num = atoi(ptr);
          break;

        case 2:
          strcpy(pStd_ptr->BOOK_in[pStd_ptr->b_idx].title, ptr);
          break;

        case 3:
          strcpy(pStd_ptr->BOOK_in[pStd_ptr->b_idx].auth, ptr);
          break;

        case 4:
          strcpy(pStd_ptr->BOOK_in[pStd_ptr->b_idx].genre, ptr);
          break;

        case 5:
          strcpy(pStd_ptr->BOOK_in[pStd_ptr->b_idx].publ, ptr);
          break;
        }
        ptr = strtok(NULL, ",");
      }
    }
    fclose(b_fp);
  }
}

void delete_BOOK()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  FILE *b_fp;
  b_fp = fopen(BOOK_FILE_NAME, "w");
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
    fclose(b_fp);
  }
}
