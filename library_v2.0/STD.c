#include "STD.h"
#include "BOOK.h"
#include "MEM.h"
#include "RENT.h"

STD_Mib std_mib;

int BOOK_SW(int F_B)
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  int i, j;

  switch (F_B)
  {
  case 1: /* 도서검색 */
    printf("\n");
    search_BOOK();
    break;

  case 2: /* 도서 추가*/
    printf(" \n");
    add_BOOK();
    break;

  case 3: /* 도서 삭제 */
    printf("\n");
    delete_BOOK();
    break;

  case 4:
    printf("뒤로가기\n ");
    break;

  default:
    printf("잘못된 숫자를 입력하셨습니다. 다시 입력해주세요. \n\n");
    break;
  }
  return 0;
};

int MEM_SW(int F_B)
{
  int i, j;
  int MEM;
  STD_Mib *pStd_ptr = GET_STD_PTR();

  switch (pStd_ptr->F_B)
  {

  case 1: /* 회원검색 */
    printf("\n");
    search_MEM();
    break;

  case 2: /* 회원 추가 */
    printf("\n");
    add_MEM();
    input_MEM();
    break;

  case 3: /* 회원삭제 */
    printf("\n");
    delete_MEM();
    break;

  case 4: /* 회원 목록 */
    printf("\n");
    MEM_list();
    printf("목록을 그만보시려면 1을 눌러주세요 : ");
    scanf("%d", &j);
    if (j == i)
    {
      break;
    }
    break;

  case 5:
    printf("뒤로가기\n ");
    break;

  default:
    printf("잘못된 숫자를 입력하셨습니다. \n\n");
    break;
  }
  return 0;
};

void STD_INIT(void)
{
  memset(&std_mib, 0x0, sizeof(std_mib));
  std_mib.rel = PROG_RUN;
}

STD_Mib *GET_STD_PTR(void)
{
  return &std_mib;
}

int RENT_SW(int F_B)
{
  int j;
  switch (F_B)
  {
  case 1:
    printf("도서 대출\n");
    rent_BOOK();
    break;

  case 2:
    printf("도서 반납\n");
    return_BOOK();
    break;

  case 3:
    printf("뒤로가기\n");
    break;
  default:
    printf("잘못된 숫자를 입력하셨습니다. \n\n");
  }

  return 0;
};