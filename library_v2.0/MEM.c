#include "MEM.h"
#include "STD.h"
#include <sys/stat.h>
#define MAX_LENGTH 256
#define ERROR_NOT_FOUND -1

int sort_MEM()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  FILE *h_fp = fopen(MEM_FILE_NAME, "rb");
  if (h_fp == NULL)
  {
    printf("파일열기 실패\n");
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
    printf("================================\n");
    printf("\n");

    //   printf(("[%ld] 회원정보\n 이름: %s 핸드폰번호: %s 성별: %s\n", i, pStd_ptr->MEM_in[pStd_ptr->h_idx].name, pStd_ptr->MEM_in[pStd_ptr->h_idx].phone, pStd_ptr->MEM_in[pStd_ptr->h_idx].gene));
    // }
    free(file_contents);
    fclose(h_fp);
  }
}

int search_MEM()
{
  int i;
  char phone[30];
  STD_Mib *pStd_ptr = GET_STD_PTR();
  printf("전화번호 : ");
  scanf("%s", phone);
  printf("\n");

  for (i = 0; i < pStd_ptr->h_idx; i++)
  {
    if (strcmp(phone, pStd_ptr->MEM_in[i].phone) == 0) // strcmp(문자열1, 문자열2 비교)
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
    printf("파일열기 실패\n");
  }
  else
  {
    printf("=============================\n");
    printf("======= 회원등록 페이지 =======\n");
    printf("=============================\n");

    // 구조체 배열에 고객 정보를 입력받음
    printf("성함 : ");
    scanf("%s", pStd_ptr->MEM_in[pStd_ptr->h_idx].name);
    printf("전화번호 뒷자리 : ");
    scanf("%s", pStd_ptr->MEM_in[pStd_ptr->h_idx].phone);
    printf("성별 : ");
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
    printf("%s 파일열기 실패\n", MEM_FILE_NAME);
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
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  FILE *h_fp = fopen(MEM_FILE_NAME, "w");
  // TODO
  /* sort_MEM 출력 ---> 삭제 ---> 업데이트 된 목록출력 */
  printf("\n\n\n");
  fclose(h_fp);
}