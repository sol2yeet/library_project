#include "MEM.h"
#include "STD.h"
#include "BOOK.h"

int MEM_list()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  FILE *h_fp = fopen(MEM_FILE_NAME, "rb");

  if (h_fp == NULL)
  {
    perror("Could not open data file");
    exit(EXIT_FAILURE);
  }
  else
  {
    char *file_contents;
    struct stat sb;
    int i = 1;

    printf("\n");
    printf("**************************[ M e m b e r   l i s t ]******************************\n\n");

    if (stat(MEM_FILE_NAME, &sb) == -1)
    {
      perror("stat");
      exit(EXIT_FAILURE);
    }

    file_contents = malloc(sb.st_size);

    while (fscanf(h_fp, "%[^\n] ", file_contents) != EOF)
    {
      printf("[%d] %s\n", i, file_contents);
      i++;
    }

    free(file_contents);
    printf("\n");
    printf("*******************************************************************************\n");
    printf("\n");
    fclose(h_fp);
  }
}

void search_MEM()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  FILE *h_fp = fopen(MEM_FILE_NAME, "rb");
  char h_phone[30];

  if (h_fp == NULL)
  {
    perror("Could not open data file");
    exit(EXIT_FAILURE);
  }
  else
  {
    printf("\t전화번호 뒤4자리를 입력하세요. : ");
    scanf("%s", h_phone);
    printf("\n");

    for (int i = 0; i < pStd_ptr->h_idx; i++)
    {
      if (strcmp(h_phone, pStd_ptr->MEM_in[i].phone) == 0)
      {
        printf("\t**** 검색된 회원 정보 ****\n\t 이름: %s \n\t 번호: %s \n\t 성별: %s \n",
               pStd_ptr->MEM_in[i].name,
               pStd_ptr->MEM_in[i].phone,
               pStd_ptr->MEM_in[i].gene);
        printf("\n");
      }
    }
  }
  fclose(h_fp);
}

void add_MEM()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  int answer;
  FILE *h_fp;
  h_fp = fopen(MEM_FILE_NAME, "a");
  int mem_line_cnt;

  if (h_fp == NULL)
  {
    perror("Could not open data file");
    exit(EXIT_FAILURE);
  }
  else
  {
    printf(">>> MAIN >> Membership >> 회원추가 -------------------------------------\n\n");
    if (h_fp != NULL)
    {
      printf("성함\t: ");
      scanf("%s", pStd_ptr->MEM_in[pStd_ptr->h_idx].name);
      printf("전화번호 뒷자리 : ");
      scanf("%s", pStd_ptr->MEM_in[pStd_ptr->h_idx].phone);
      printf("성별\t: ");
      scanf("%s", pStd_ptr->MEM_in[pStd_ptr->h_idx].gene);
      printf("\n");

      printf("등록하시하시겠습니까?\n  1.넵 \t2.아니오  ");
      // scanf("%d", &pStd_ptr->BOOK_in[pStd_ptr->b_idx].b_sta);
      scanf("%d", &answer);
      switch (answer)
      {

      case 1:

        fprintf(h_fp, "%s, %s, %s\r\n",
                pStd_ptr->MEM_in[pStd_ptr->h_idx].name,
                pStd_ptr->MEM_in[pStd_ptr->h_idx].phone,
                pStd_ptr->MEM_in[pStd_ptr->h_idx].gene);
        pStd_ptr->h_idx++;

        printf("\n");
        printf(" 회원 등록이 완료되었습니다. 초기화면으로 돌아갑니다...");
        break;

      case 2:
        MEM_SW(answer);
        break;

      default:
        break;
      }
      fclose(h_fp);
    }
  }
}

void input_MEM()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  FILE *h_fp = fopen(MEM_FILE_NAME, "r");
  char line[150];
  char *ptr;
  int word_cnt;

  if (h_fp == NULL)
  {
    perror("Could not open data file");
    exit(EXIT_FAILURE);
  }

  else
  {
    printf(" ");
    while (fscanf(h_fp, "%s", line) > 0)
    {
      if (word_cnt > 3)
      {
        word_cnt = 0;
        pStd_ptr->h_idx++;
      }
      ptr = strtok(line, ",");
      word_cnt++;
      {
        switch (word_cnt)
        {
        case 1:
          strcpy(pStd_ptr->MEM_in[pStd_ptr->h_idx].name, ptr);
          break;

        case 2:
          strcpy(pStd_ptr->MEM_in[pStd_ptr->h_idx].phone, ptr);
          break;

        case 3:
          strcpy(pStd_ptr->MEM_in[pStd_ptr->h_idx].gene, ptr);
          break;
        }
        ptr = strtok(NULL, ",");
      }
    }
    fclose(h_fp);
  }
}

void delete_MEM()

{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  int b_fp = open(MEM_FILE_NAME, O_RDWR);
  size_t file_size = lseek(b_fp, 0, SEEK_END);
  char *addr = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, b_fp, 0);
  int line_cnt;
  char del_member[30];

  if (b_fp == ERROR_NOT_FOUND)
  {
    perror("Could not open data file");
    exit(EXIT_FAILURE);
  }
  else
  {
    printf("\n");
    printf(">>> MAIN >> Member >> 회원삭제 ----------------------------------------\n\n");

    printf("삭제할 회원의 번호을 입력해 주세요: ");
    scanf("%s", del_member);
    printf("\n");

    line_cnt = Get_bookfile_line(addr, file_size, ELEM_TYPE_PHONE, del_member);

    Delete_book_file_line(b_fp, addr, file_size, line_cnt);
    printf("회원이 삭제되었습니다.");

    munmap(addr, file_size);

    printf("\n");
    close(b_fp);
  }
}