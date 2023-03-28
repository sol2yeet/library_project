#include "MEM.h"
#include "STD.h"
#include "BOOK.h"

int sort_MEM()
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

    printf("=============================\n");
    printf("========== 회원 목록 =========\n");
    printf("=============================\n");

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
    printf("\n");
    printf("================================\n\n");

    free(file_contents);
    fclose(h_fp);
  }
}

int search_MEM()
{
  int i;
  char phone[30];
  STD_Mib *pStd_ptr = GET_STD_PTR();
  printf("\t전화번호 : ");
  scanf("%s", phone);
  printf("\n");

  for (i = 0; i < pStd_ptr->h_idx; i++)
  {
    if (strcmp(phone, pStd_ptr->MEM_in[i].phone) == 0)
      return i;
  }
  printf("\n");
  return ERROR_NOT_FOUND;
}

void add_MEM()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();

  FILE *h_fp = NULL;
  h_fp = fopen(MEM_FILE_NAME, "a");
  if (h_fp == NULL)
  {
    perror("Could not open data file");
    exit(EXIT_FAILURE);
  }
  else
  {
    printf("=============================\n");
    printf("======= 회원등록 페이지 =======\n");
    printf("=============================\n");

    // 구조체 배열에 고객 정보를 입력받음
    printf("성함\t: ");
    scanf("%s", pStd_ptr->MEM_in[pStd_ptr->h_idx].name);
    printf("전화번호 뒷자리 : ");
    scanf("%s", pStd_ptr->MEM_in[pStd_ptr->h_idx].phone);
    printf("성별\t: ");
    scanf("%s", pStd_ptr->MEM_in[pStd_ptr->h_idx].gene);
    printf("\n");

    fprintf(h_fp, "%s, %s, %s\r\n", pStd_ptr->MEM_in[pStd_ptr->h_idx].name, pStd_ptr->MEM_in[pStd_ptr->h_idx].phone, pStd_ptr->MEM_in[pStd_ptr->h_idx].gene);
    pStd_ptr->h_idx++;

    printf("\n%d 번째 회원 입니다.\n", pStd_ptr->h_idx);
    printf("\n\n");

    fclose(h_fp);
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
    // 회원파일 입력
    while (fscanf(h_fp, "%s", line) > 0)
    {
      word_cnt = 0;
      ptr = strtok(line, ",");
      while (ptr != NULL)
      {
        if (word_cnt > 3)
        {
          word_cnt = 0;
          pStd_ptr->h_idx++;
        }

        switch (word_cnt)
        {
        case 1: // char name
          strcpy(pStd_ptr->MEM_in[pStd_ptr->h_idx].name, ptr);
          break;

        case 2: // char phone
          strcpy(pStd_ptr->MEM_in[pStd_ptr->h_idx].phone, ptr);
          break;

        case 3: // char gene
          strcpy(pStd_ptr->MEM_in[pStd_ptr->h_idx].gene, ptr);
          break;
        }
        ptr = strtok(NULL, ",");

        // strtok 문자열 자르기
        // atoi 문자 >>> 숫자 변환
      }
    }
    fclose(h_fp);
    // 회원정보 입력
  }
}

void delete_MEM()

// 입력받기
// 입력받은 문자열과 비교
// 해당 줄수 리턴
// 해당줄의 맨앞과 맨뒤 구해서 삭제

{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  int b_fp = open(MEM_FILE_NAME, O_RDWR);
  size_t file_size = lseek(b_fp, 0, SEEK_END);
  char *addr = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, b_fp, 0);
  int line_cnt;
  char del_member[30];

  if (b_fp == NULL)
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

    // 찾는 조건을 입력하고 해당 줄수를 리턴 받기
    line_cnt = Get_bookfile_line(addr, file_size, ELEM_TYPE_TITLE, del_member);

    // printf("삭제할 줄의 번호는 %d입니다.\n", line_cnt);
    //  삭제
    Delete_book_file_line(b_fp, addr, file_size, line_cnt);
    printf("회원이 삭제되었습니다.");

    munmap(addr, file_size); // 메모리 매핑 해제

    printf("\n");
    close(b_fp);
  }
}