#ifndef _MEM_H_
#define _MEM_H_

#include "STD.h"

/*
#회원관리 (등록,삭제) << 도서관리와 비슷하게 구성
1. 회원검색
2. 회원추가 (이름, 성별, 핸드폰번호) 이름으로 검색시 중복이 발생할 수 있으므로 핸드폰 번호로 검색
3. 회원삭제
txt 파일로
*/

int search_MEM()
{
  int i;
  char phone[30];
  printf("전화번호 : ");
  scanf("%s", phone);

  for (i = 0; i < h_idx; i++)
  {
    if (strcmp(phone, MEM_in[i].phone) == 0) // strcmp(문자열1, 문자열2 비교)
      return i;
  }
  return -2; // 음수를 사용하여 정확하게 표현
}

void add_MEM()
{
  FILE *h_fp = fopen("MEM,txt", "a");

  // 구조체 배열에 고객 정보를 입력받음
  printf("고객 이름 : ");
  scanf("%s", MEM_in[h_idx].name);
  printf("전화 번호 : ");
  scanf("%s", MEM_in[h_idx].phone);
  printf("성별 : ");
  scanf("%s", MEM_in[h_idx].gene);

  fprintf(h_fp, "\n%s, %s, %s", MEM_in[h_idx].name, MEM_in[h_idx].phone, MEM_in[h_idx].gene);
  h_idx++;
  // 회원수 추가
  fclose(h_fp);
}

void input_MEM()
{
  FILE *h_fp = fopen("MEM.txt", "r");
  char line[150];
  char *ptr;
  int word_cnt;

  // 회원파일 입력
  while (fscanf(h_fp, "%s", line) > 0)
  {
    word_cnt = 0;
    ptr = strtok(line, ",");
    while (ptr != NULL)
    {
      word_cnt++;

      switch (word_cnt)
      {
      case 1: // char name
        strcpy(MEM_in[h_idx].name, ptr);
        break;

      case 2: // char phone
        strcpy(MEM_in[h_idx].phone, ptr);
        break;

      case 3: // char gene
        strcpy(MEM_in[h_idx].gene, ptr);
        break;
      }
      ptr = strtok(NULL, ",");

      // strtok 문자열 자르기
      // atoi 문자 >>> 숫자 변환
    }
    h_idx++;
  }
  fclose(h_fp);
  // 회원정보 입력
}

void del_MEM()
{
  FILE *h_fp = fopen("MEM.txt", "w"); // 기존 삭제 기능 활용

  // 구조체 배열에 고객 정보를 입력 받음
  printf("회원 이름 : ");
  scanf("%s", MEM_in[h_idx].name);

  printf("전화번호 : ");
  scanf("%s", MEM_in[h_idx].phone);

  printf("성별 : ");
  scanf("%s", MEM_in[h_idx].gene);

  fprintf(h_fp, "\n%s, %s, %s", MEM_in[h_idx].name, MEM_in[h_idx].phone, MEM_in[h_idx].gene);

  fclose(h_fp);
}

#endif /*_MEM_H_*/