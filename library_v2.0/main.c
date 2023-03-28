#include "STD.h"  // 함수 변수
#include "BOOK.h" // 책
#include "MEM.h"  // 회원
#include "RENT.h" // 대여 반납

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
    printf("\n\n");
    printf("--------------도서관 공사중-----------------\n");
    printf("|                                         |\n");
    printf("|             1. Book                     |\n");
    printf("|             2. Membership               |\n");
    printf("|             3. Rent & Return            |\n");
    printf("|             4. EXIT --->                |\n");
    printf("|                                         |\n");
    printf("|-----------------------------------------|\n");
    printf("입력 : ");
    scanf(" %d", &(pStd_ptr->F_A));

    switch (pStd_ptr->F_A)
    {
    case 1:
      printf("\n");
      printf("|>> MAIN >>---------BOOK-----------------|\n");
      printf("|                                        |\n");
      printf("|               1. 검색                  |\n");
      printf("|               2. 추가                  |\n");
      printf("|               3. 삭제                  |\n");
      printf("|               4. MAIN --->             |\n");
      printf("|                                        |\n");
      printf("|----------------------------------------|\n");
      printf("입력 : ");
      scanf("%d", &(pStd_ptr->F_B));
      BOOK_SW(pStd_ptr->F_B);
      break;

    case 2:
      printf("\n");
      printf("|>> MAIN >>------Membership--------------|\n");
      printf("|                                        |\n");
      printf("|               1. 검색                  |\n");
      printf("|               2. 등록                  |\n");
      printf("|               3. 삭제                  |\n");
      printf("|               4. MAIN --->             |\n");
      printf("|                                        |\n");
      printf("|----------------------------------------|\n");
      printf("입력 (5번 전체목록): ");
      // printf("4. 회원 목록 보기 \n");
      scanf("%d", &(pStd_ptr->F_B));
      MEM_SW(pStd_ptr->F_B);
      break;

    case 3: /* 대출 반납 */
      printf("\n");
      printf("|>> MAIN >>------Membership--------------|\n");
      printf("|                                        |\n");
      printf("|               1. 대출                  |\n");
      printf("|               2. 반납                  |\n");
      printf("|               3. MAIN --->             |\n");
      printf("|                                        |\n");
      printf("|----------------------------------------|\n");
      printf("입력 : ");
      scanf("%d", &(pStd_ptr->F_B));
      RENT_SW(pStd_ptr->F_B);
      break;

    case 4: /* 종료 */
      // printf(" 곧 오픈합니다. 또 오세용 (찡긋) \n");
      pStd_ptr->rel = 0;
      break;

    default:
      printf(" 화면에 표시된 번호를 입력해 주세요.");
    }
  }
  return 0;
}