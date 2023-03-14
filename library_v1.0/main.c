/* 도서관리 프로그램 목표기능
1. 도서관리 현황
2. 도서관리 (추가, 삭제, 대여, 반납)
3. 회원관리 (등록/삭제) -> 도서관리와 비슷
*/

#include "STD.h"  // 함수 변수
#include "BOOK.h" // 책
#include "MEM.h"  // 회원
// #include "RENT.h" // 대여 반납

int main()
{

  input_BOOK(); // 책 정보 입력
  input_MEM();  // 회원정보 입력
  // input_RENT();   // 대여정보 입력
  // input_RETURN(); // 반납정보 입력

  while (rel != 0)
  {
    printf("------------------------------\n");
    printf("도서 관리 프로그램입니다. \n");
    printf("1. 도서관리\n");
    printf("2. 회원관리 \n");
    printf("3. 대출 및 반납, 연체현황 \n");
    printf("4. 나가기 \n");
    printf(" 원하는 기능을 선택 해주세요 : \n");
    scanf("%d", &F_A);
    printf("------------------------------\n");
    printf("\n");

    switch (F_A)
    {
    case 1:
      printf("------------------------------\n");
      printf(" 도서 관리 기능 화면 입니다. \n");
      printf("1. 도서 검색\n");
      printf("2. 도서 추가 \n");
      printf("3. 도서 삭제 \n");
      printf("4. 전체 도서 목록 불러오기 \n");
      printf("5. 이전 페이지로 돌아가기 \n");
      printf(" 원하는 기능을 선택 해주세요 : \n");
      scanf("%d", &F_B);
      printf("------------------------------\n");
      BOOK_SW(F_B);
      break;

    case 2:
      printf("------------------------------\n");
      printf(" 회원 관리 기능 화면 입니다. \n");
      printf("1. 회원 검색\n");
      printf("2. 회원 추가 \n");
      printf("3. 회원 삭제 \n");
      printf("4. 전체 회원 목록 불러오기 \n");
      printf("5. 이전 페이지로 돌아가기 \n");
      printf(" 원하는 기능을 선택 해주세요 : \n");
      scanf("%d", &F_B);
      printf("------------------------------\n");
      BOOK_SW(F_B);
      break;

    case 3:
      printf("-------------------------------------\n");
      printf(" 도서 대출 반납 연체현황 기능 화면 입니다. \n");
      printf("1. 도서 대출 \n");
      printf("2. 도서 반납 \n");
      printf("3. 도서 연체 현황 \n");
      printf("4. 이전 페이지로 돌아가기 \n");
      printf(" 원하는 기능을 선택 해주세요 : \n");
      scanf("%d", &F_B);
      printf("-------------------------------------\n");
      BOOK_SW(F_B);
      break;

    case 4:
      printf("프로그램 종료하기\n");
      rel = 0;
      break;

    default:
      printf("잘못된 숫자를 입력하셨습니다. 다시 입력해 주세요.");
    }
  }
  return 0;
}