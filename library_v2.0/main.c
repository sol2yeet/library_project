#include "STD.h"  // 함수 변수
#include "BOOK.h" // 책
#include "MEM.h"  // 회원
#include "RENT.h" // 대여 반납
#define BUFFER_SIZE 1024

int main()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  STD_INIT();

  input_BOOK();   // 책 정보 입력
  input_MEM();    // 회원정보 입력
  input_RENT();   // 대여정보 입력
  input_RETURN(); // 반납정보 입력

  while (pStd_ptr->rel != 0)
  {
    printf("===========================\n");
    printf("도서 관리 프로그램입니다.\n");
    printf("===========================\n");
    printf("1. 도서 관리\n");
    printf("2. 회원 관리 \n");
    printf("3. 대출 및 반납 현황 \n");
    printf("4. 나가기 \n");
    printf("원하는 기능을 선택 해주세요 :\n");
    scanf(" %d", &(pStd_ptr->F_A));
    printf("\n");

    switch (pStd_ptr->F_A)
    {
    case 1: /* 도서 */
      printf("=============================\n");
      printf("=== 도서관리 페이지 ====\n");
      printf("=============================\n");
      printf("1. 도서 검색\n");
      printf("2. 도서 추가 \n");
      printf("3. 도서 삭제 \n");
      printf("4. 도서 목록 보기 \n");
      printf("5. 이전 페이지로 돌아가기 \n");
      printf(" 원하는 기능을 선택 해주세요 : \n");
      scanf("%d", &(pStd_ptr->F_B));
      printf("\n");
      BOOK_SW(pStd_ptr->F_B);
      break;

    case 2: /* 회원 */
      printf("=============================\n");
      printf("=== 회원관리 페이지 ====\n");
      printf("=============================\n");
      printf("1. 회원 검색\n");
      printf("2. 회원 등록 \n");
      printf("3. 회원 삭제 \n");
      printf("4. 회원 목록 보기 \n");
      printf("5. 이전 페이지로 돌아가기 \n");
      printf(" 원하는 기능을 선택 해주세요 : \n");
      scanf("%d", &(pStd_ptr->F_B));
      printf("\n");
      MEM_SW(pStd_ptr->F_B);
      break;

    case 3: /* 대출 반납 */
      printf("=============================\n");
      printf("===도서 대출반납 페이지===\n");
      printf("=============================\n");
      printf("1. 도서 대출\n");
      printf("2. 도서 반납 \n");
      printf("3. 도서 연체 현황 \n");
      printf("4. 회원 목록 보기 \n");
      printf("5. 이전 페이지로 돌아가기 \n");
      printf("원하는 기능을 선택 해주세요 : \n");
      scanf("%d", &(pStd_ptr->F_B));
      printf("\n");
      MEM_SW(pStd_ptr->F_B);
      break;

    case 4: /* 종료 */
      printf("프로그램 종료하기\n");
      pStd_ptr->rel = 0;
      break;

    default:
      printf("잘못된 번호입니다. 다시 입력해 주세요.");
    }
  }
  return 0;
}