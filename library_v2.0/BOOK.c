#include "BOOK.h"
#include "STD.h"
#include <sys/stat.h>
#define ERROR_NOT_FOUND -1

int search_BOOK()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  FILE *b_fp = fopen(BOOK_FILE_NAME, "rb");
  if (b_fp == NULL)
  {
    perror("Could not open data file");
    exit(EXIT_FAILURE);
  }
  else
  {
    int list_answer;
    char title[30];
    char category[30];
    int i, j;
    struct stat sk;
    char *file_contents;
    printf(">>> MAIN >> BOOK >> 도서검색 -------------\n\n");
    printf("     1. 제목으로 검색\n");
    printf("     2. 장르별 검색\n");
    printf("     3. 전체 목록 보기\n");
    printf("     4. 이전 화면으로 돌아가기\n");
    printf("     입력 : ");
    scanf("%d", &list_answer);
    switch (list_answer)
    {
    case 1:
      printf(">>> BOOK >> 도서검색 >>-----제목을 입력하세요 : ");
      scanf("%s", title);
      printf("\n");

      for (int i = 0; i < pStd_ptr->b_idx; i++)
      {
        // printf("#%d %s/%s\n", i, title, pStd_ptr->BOOK_in[i].title); //test
        if (strcmp(title, pStd_ptr->BOOK_in[i].title) == 0)
        {
          printf("-------> 검색된 도서 정보 \n\t 제목: %s \n\t 장르: %s \n\t 작가: %s \n\t 출판사: %s\n", pStd_ptr->BOOK_in[i].title, pStd_ptr->BOOK_in[i].genre, pStd_ptr->BOOK_in[i].auth, pStd_ptr->BOOK_in[i].publ);
          break;
        }
        else
        {
          printf("입력한 제목에 일치하는 책이 없습니다.\n");
        }
      }
      break;
    case 2:
      printf(">>> BOOK >> 도서검색 >>-----장르를 입력하세요 : ");
      scanf("%s", category);
      printf("\n");

      for (int i = 0; i < pStd_ptr->b_idx; i++)
      {
        if (strcmp(category, pStd_ptr->BOOK_in[i].genre) == 0)
        {
          // FIXME : 결과가 1개만 검색됨
          printf("-------> 검색된 도서 정보 \n\t 제목: %s \n\t 장르: %s \n\t 작가: %s \n\t 출판사: %s\n", pStd_ptr->BOOK_in[i].title, pStd_ptr->BOOK_in[i].genre, pStd_ptr->BOOK_in[i].auth, pStd_ptr->BOOK_in[i].publ);
          break;
        }
        else
        {
          printf("입력한 정보에 일치하는 책이 없습니다.\n");
        }
      }
      break;
    case 3:
      printf("\n");
      printf("*********************[도서목록]**********************\n\n");
      if (stat(BOOK_FILE_NAME, &sk) == -1)
      {
        perror("stat");
        exit(EXIT_FAILURE);
      }
      file_contents = malloc(sk.st_size);
      i = 1;
      while (fscanf(b_fp, "%[^\n] ", file_contents) != EOF)
      {
        printf(" [%d] %s\n", i, file_contents);
        i++;
      }
      free(file_contents);
      printf("\n");
      printf("*****************************************************\n");
      printf("     메인화면으로 돌아가려면 1을 입력해 주세요 : ");
      scanf("%d", &j);
      if (j == 1)
      {
        break;
      }
    case 4:
      break;
    default:
      printf("잘못된 번호입니다. 다시 입력해 주세요.");
    }
    fclose(b_fp);
  }
}

// int search_BOOK()
// {
//   STD_Mib *pStd_ptr = GET_STD_PTR();
//   int val = -3;
//   char title[30];
//   printf("=============================\n");
//   printf("======= 도서검색 페이지 =======\n");
//   printf("=============================\n");
//   printf("제목을 입력하세요 : ");
//   scanf("%s", title);
//   printf("\n");
//   for (int i = 0; i < pStd_ptr->b_idx; i++)
//   {
//     printf("#%d %s/%s\n", i, title, pStd_ptr->BOOK_in[i].title);
//     if (strcmp(title, pStd_ptr->BOOK_in[i].title) == 0)
//     {
//       val = i;
//       break;
//     }
//   }
//   printf("\n");
//   return val;
// }

void add_BOOK()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();

  FILE *b_fp;
  b_fp = fopen(BOOK_FILE_NAME, "a");

  if (b_fp == NULL)
  {
    perror("Could not open data file");
    exit(EXIT_FAILURE);
  }
  else
  {
    printf(">>> MAIN >> BOOK >> 도서추가 -------------\n\n");
    if (b_fp != NULL)
    {
      printf("   식별번호 : ");
      scanf("%d", &pStd_ptr->BOOK_in[pStd_ptr->b_idx].book_num);
      printf("   제목 : ");
      scanf("%s", pStd_ptr->BOOK_in[pStd_ptr->b_idx].title);
      printf("   작가 : ");
      scanf("%s", pStd_ptr->BOOK_in[pStd_ptr->b_idx].auth);
      printf("   장르 : ");
      scanf("%s", pStd_ptr->BOOK_in[pStd_ptr->b_idx].genre);
      printf("   출판사 : ");
      scanf("%s", pStd_ptr->BOOK_in[pStd_ptr->b_idx].publ);
      printf("   도서를 등록합니다. (1 : 입력) : ");
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
      printf("   (빠밤!)도서가 등록되었습니다. \n\n");
      fclose(b_fp);
    }
  }
}

void input_BOOK()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  FILE *b_fp;
  char line[150];
  char *ptr;
  int word_cnt = 0;
  b_fp = fopen(BOOK_FILE_NAME, "r");
  if (b_fp == NULL)
  {
    perror("Could not open data file");
    exit(EXIT_FAILURE);
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
      ptr = strtok(line, ",");
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
    perror("Could not open data file");
    exit(EXIT_FAILURE);
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
