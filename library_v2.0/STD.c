#include "STD.h"
#include "BOOK.h"
#include "MEM.h"
#include "RENT.h"
STD_Mib std_mib;

int BOOK_SW(int F_B)
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  int i, j;
  // int book;

  switch (F_B)
  {
  case 1: /* 도서검색 */
    printf("\n");
    search_BOOK();
    // book = search_BOOK();
    //  if (book == -3)
    //  {
    //    printf("입력한 제목에 일치하는 책이 없습니다.\n");
    //  }
    //  else
    //  {
    //    printf("도서 정보 \n 제목: %s 장르: %s 작가: %s 출판사: %s\n", pStd_ptr->BOOK_in[book].title, pStd_ptr->BOOK_in[book].genre, pStd_ptr->BOOK_in[book].auth, pStd_ptr->BOOK_in[book].publ);
    //  }
    break;

  case 2: /* 도서 추가*/
    printf(" \n");
    add_BOOK();
    break;

  case 3: /* 도서 삭제 */
    printf("\n");
    delete_BOOK();
    break;

    // case 4: /* 책 목록 */
    // printf("\n");
    // sort_BOOK();
    //  for (i = 0; i < pStd_ptr->b_idx; i++)
    //  {
    //    printf("도서 정보 \n 제목: %s 장르: %s 작가: %s 출판사: %s", pStd_ptr->BOOK_in[pStd_ptr->b_idx].title, pStd_ptr->BOOK_in[pStd_ptr->b_idx].genre, pStd_ptr->BOOK_in[pStd_ptr->b_idx].auth, pStd_ptr->BOOK_in[pStd_ptr->b_idx].publ);
    //  }
    //  printf("\n");
    // printf("다른 기능을 선택하려면 1을 눌러주세요 : ");
    // scanf("%d", &j);
    // if (j == i)
    //{
    //   break;
    // }

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
    MEM = search_MEM();
    if (MEM == -2)
    {
      printf("입력한 정보에 일치하는 회원이 없습니다.\n");
    }
    else
    {
      printf("회원정보\n 이름: %s 핸드폰번호: %s 성별: %s\n", pStd_ptr->MEM_in[MEM].name, pStd_ptr->MEM_in[MEM].phone, pStd_ptr->MEM_in[MEM].gene);
    }
    break;

  case 2: /* 회원 추가 */
    printf(" \n");
    add_MEM();
    input_MEM();
    break;

  case 3: /* 회원삭제 */
    printf("\n");
    delete_MEM();
    break;

  case 5: /*전체 회원 목록 불러오기 */
    printf("\n");
    sort_MEM();
    // for (i = 0; i < pStd_ptr->h_idx; i++)
    // {
    //   printf("회원정보\n 이름: %s 핸드폰번호: %s 성별: %s\n",  pStd_ptr->MEM_in[MEM].name,  pStd_ptr->MEM_in[MEM].phone,  pStd_ptr->MEM_in[MEM].gene);
    // }
    // printf("\n");
    printf("다른 기능을 선택하려면 1을 눌러주세요 : ");
    scanf("%d", &j);
    if (j == i)
    {
      break;
    }
  case 4:
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

  // 각 기능별 인덱스(순서)
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

    // case :
    //   printf("대여현황\n");
    //   rent_list();
    //   printf("\n");
    //   printf("목록을 그만 보고 싶으면 1을 눌러 주세요 : ");
    //   scanf("%d", &j);
    //   printf("\n");
    //   if (j == 1)
    //   {
    //     break;
    //   }

  case 3:
    printf("뒤로가기\n");
    break;
  default:
    printf("잘못된 숫자를 입력하셨습니다. \n\n");
  }
  return 0;
};