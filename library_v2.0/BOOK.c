#include "BOOK.h"
#include "RENT.h"
#include "STD.h"

void Book_list(char *file, char *pfile_data)
{
  struct stat sk;
  int i = 1;

  printf("\n");
  printf("**************************[ B o o k   l i s t ]******************************\n\n");

  if (stat(BOOK_FILE_NAME, &sk) == ERROR_NOT_FOUND)
  {
    perror("stat");
    exit(EXIT_FAILURE);
  }

  pfile_data = malloc(sk.st_size);
  while (fscanf((FILE *)file, "%[^\n] ", pfile_data) != EOF)
  {
    printf("\t [%d] %s\n", i, pfile_data);
    i++;
  }

  free(pfile_data);

  printf("\n");
  printf("*******************************************************************************\n");
  printf("\n");
}

void search_BOOK()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  FILE *b_fp = fopen(BOOK_FILE_NAME, "rb");
  int list_answer;
  char title[30];
  char category[30];
  char *file_contents;
  int answer;
  int i, j;

  if (b_fp == NULL)
  {
    perror("Could not open data file");
    exit(EXIT_FAILURE);
  }
  else
  {
    printf(">>> MAIN >> BOOK >> 도서검색 --------------------------------\n\n");
    printf("\t1. 제목으로 검색\n");
    printf("\t2. 장르별 검색\n");
    printf("\t3. 전체 목록 보기\n");
    printf("\t4. 상위 페이지로 ..\n\n");
    printf("\t입력 : ");
    scanf("%d", &list_answer);

    switch (list_answer)
    {

    case 1:
      printf("\t제목을 입력하세요 : ");
      scanf("%s", title);
      printf("\n");

      for (int i = 0; i < pStd_ptr->b_idx; i++)
      {
        if (strcmp(title, pStd_ptr->BOOK_in[i].title) == 0)
        {
          printf("\t**** 검색된 도서 정보 ****\n\t 제목: %s \n\t 장르: %s \n\t 작가: %s \n\t 출판: %s\n",
                 pStd_ptr->BOOK_in[i].title,
                 pStd_ptr->BOOK_in[i].genre,
                 pStd_ptr->BOOK_in[i].auth,
                 pStd_ptr->BOOK_in[i].publ);
          printf("\n");
        }

        // TODO: 도서 검색 후 옵션으로 이동 1. 대출(회원) \t 2.삭제(관리자)
        //   printf("\t 옵션을 선택하세요 \n\t 1. 대출(회원) \t 2.삭제(관리자)");
        //   scanf("%s", &answer);
        //   printf("\n");
        //   if (answer == 1)
        //   {
        //     delete_BOOK();
        //   }
      }
      break;

    case 2:
      printf("\t장르를 입력하세요 : ");
      scanf("%s", category);
      printf("\n");

      for (int i = 0; i < pStd_ptr->b_idx; i++)
      {
        if (strcmp(category, pStd_ptr->BOOK_in[i].genre) == 0)
        {
          printf("-------> 검색된 도서 정보 \n\t 제목: %s \n\t 장르: %s \n\t 작가: %s \n\t 출판사: %s\n", pStd_ptr->BOOK_in[i].title, pStd_ptr->BOOK_in[i].genre, pStd_ptr->BOOK_in[i].auth, pStd_ptr->BOOK_in[i].publ);

          printf("\n");
          printf("1. 계속보기 -> \t 2. 초기화면으로");
          scanf("%d", &answer);
          if (answer == 1)
          {
            RENT_SW(answer);
          }
          else
            break;
        }
      }
      break;

    case 3:
      Book_list((char *)b_fp, file_contents);
      printf("\t (!) 목록에서 원하는 도서를 찾으시려면 1을 입력해 주세요 : \n");
      scanf("%d", &j);
      while (j != ERROR_NOT_FOUND)
      {
        if (j == 1)
        {
          BOOK_SW(j);
          break;
        }
        else
        {
          printf("잘못된 입력입니다.\n");
        }
      }

    case 4:
      break;
    default:
      printf("잘못된 번호입니다. 다시 입력해 주세요.");
    }
    fclose(b_fp);
  }
}

void add_BOOK()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  int answer;
  FILE *b_fp;
  b_fp = fopen(BOOK_FILE_NAME, "a");

  if (b_fp == NULL)
  {
    perror("Could not open data file");
    exit(EXIT_FAILURE);
  }
  else
  {
    printf(">>> MAIN >> BOOK >> 도서추가 ----------------------------------------\n\n");
    if (b_fp != NULL)
    {
      printf("제목\t: ");
      scanf("%s", pStd_ptr->BOOK_in[pStd_ptr->b_idx].title);
      printf("작가\t: ");
      scanf("%s", pStd_ptr->BOOK_in[pStd_ptr->b_idx].auth);
      printf("장르\t: ");
      scanf("%s", pStd_ptr->BOOK_in[pStd_ptr->b_idx].genre);
      printf("출판사\t: ");
      scanf("%s", pStd_ptr->BOOK_in[pStd_ptr->b_idx].publ);
      printf("\n");
      printf("등록하시하시겠습니까?\n  1.넵 \t2.아니오  ");
      // scanf("%d", &pStd_ptr->BOOK_in[pStd_ptr->b_idx].b_sta);
      scanf("%d", &answer);
      switch (answer)
      {

      case 1:
        pStd_ptr->BOOK_in[pStd_ptr->b_idx].b_sta = 1; // 도서있음(1) / 도서 없음(0)
        fprintf(b_fp, "%s, %s, %s, %s, %d\r\n",
                pStd_ptr->BOOK_in[pStd_ptr->b_idx].title,
                pStd_ptr->BOOK_in[pStd_ptr->b_idx].auth,
                pStd_ptr->BOOK_in[pStd_ptr->b_idx].genre,
                pStd_ptr->BOOK_in[pStd_ptr->b_idx].publ,
                pStd_ptr->BOOK_in[pStd_ptr->b_idx].b_sta // 도서있음(1) / 도서 없음(0)
        );
        pStd_ptr->b_idx++;
        printf("\n");
        printf(" (!! 빠밤 !!) 도서가 등록되었습니다.\n 초기화면으로 돌아갑니다...\n");
        break;

      case 2:
        BOOK_SW(answer);
        break;

      default:
        break;
      }
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
      if (word_cnt > 4)
      {
        word_cnt = 0;
        pStd_ptr->b_idx++;
      }
      ptr = strtok(line, ",");
      word_cnt++;
      {
        switch (word_cnt)
        {

        case 1:
          strcpy(pStd_ptr->BOOK_in[pStd_ptr->b_idx].title, ptr);
          break;

        case 2:
          strcpy(pStd_ptr->BOOK_in[pStd_ptr->b_idx].auth, ptr);
          break;

        case 3:
          strcpy(pStd_ptr->BOOK_in[pStd_ptr->b_idx].genre, ptr);
          break;

        case 4:
          strcpy(pStd_ptr->BOOK_in[pStd_ptr->b_idx].publ, ptr);
          break;
        }
        ptr = strtok(NULL, ",");
      }
    }
    fclose(b_fp);
  }
}

int Get_bookfile_line(char *pfile_data, size_t file_size, char type, char *find_string)
{
  char temp_string[TYPE_LEN] = {0};
  char proc_string[TYPE_LEN] = {0};
  int i;
  int proc_cnt = 0;
  int temp_cnt = 0;
  int comma_cnt = 0;
  int line_cnt = 0;

  for (i = 0; i < strlen(find_string); i++)
  {
    if (find_string[i] != ASCII_SPACE)
    {
      proc_string[proc_cnt++] = find_string[i];
    }
  }
  for (i = 0; i < file_size; i++)
  {
    if (pfile_data[i] != ASCII_COMMA && pfile_data[i] != ASCII_SPACE)
    {
      temp_string[temp_cnt++] = pfile_data[i];
    }
    else if (pfile_data[i] == ASCII_COMMA)
    {
      if ((comma_cnt == type) && (strncmp(temp_string, proc_string, proc_cnt) == 0))
      {
        break;
      }
      memset(temp_string, 0x0, TYPE_LEN);
      temp_cnt = 0;
      comma_cnt++;
    }
    if (pfile_data[i] == ASCII_LINEFEED)
    {
      memset(temp_string, 0x0, TYPE_LEN);
      temp_cnt = 0;
      comma_cnt = 0;
      line_cnt++;
    }
  }
  return line_cnt + 1;
}

void Delete_book_file_line(int file, char *pfile_data, size_t file_size, int line_cnt)
{
  int offset = 0;
  size_t size_to_delete = 0;
  int curr_lint_cnt = 1;

  for (int i = 0; i < file_size; i++)
  {
    if (pfile_data[i] == ASCII_LINEFEED)
    {
      if (line_cnt == curr_lint_cnt)
      {
        break;
      }
      curr_lint_cnt++;
      size_to_delete = 0;
    }
    size_to_delete++;
    {
      offset++;
    }
  }

  offset = offset - size_to_delete;

  memmove((char *)pfile_data + offset, (char *)pfile_data + offset + size_to_delete, file_size - offset - size_to_delete);

  lseek(file, file_size - size_to_delete, SEEK_SET);
  ftruncate(file, file_size - size_to_delete);
}

void delete_BOOK()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  int b_fp = open(BOOK_FILE_NAME, O_RDWR);
  size_t file_size = lseek(b_fp, 0, SEEK_END);
  char *addr = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, b_fp, 0);
  int line_cnt;
  char rent_book[30];

  if (b_fp == ERROR_NOT_FOUND)
  {
    perror("Could not open data file");
    exit(EXIT_FAILURE);
  }
  else
  {
    printf("\n");
    printf(">>> MAIN >> BOOK >> 도서삭제 ----------------------------------------\n\n");

    printf("삭제할 도서의 제목을 입력해 주세요: ");
    scanf("%s", rent_book);
    printf("\n");

    line_cnt = Get_bookfile_line(addr, file_size, ELEM_TYPE_TITLE, rent_book);

    Delete_book_file_line(b_fp, addr, file_size, line_cnt);
    printf("도서가 삭제되었습니다.");

    munmap(addr, file_size);

    printf("\n");
    close(b_fp);
  }
}
