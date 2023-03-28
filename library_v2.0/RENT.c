#include "RENT.h"
#include "BOOK.h"
#include "STD.h"

void Set_bookfile_rent_stat(char *pfile_data, size_t file_size, int line_cnt, char rent_stat)
{
  int curr_lint_cnt = 0;

  for (int i = 0; i < file_size; i++)
  {
    if (pfile_data[i] == ASCII_LINEFEED)
    {
      curr_lint_cnt++;
      if (line_cnt == curr_lint_cnt)
      {
        if (pfile_data[i - 1] == '0')
        {
          printf("(!) 대여중인 도서입니다. 다른 책을 검색해주세요.\n\n");
          rent_BOOK();
        }
        else
        {
          pfile_data[i - 1] = rent_stat;
          printf("대여가 완료되었습니다. 메인페이지로 돌아갑니다.");
          // printf("%c\n", pfile_data[i - 1]);
          break;
        }
      }
    }
  }
}

void rent_BOOK() // 도서대출 - 회원용
{

  /* TODO:
  1. 회원의 대출 권수를 알수있는 변수를 선언하고 회원파일에 적용(index).
  2. 최대 대출권수 제한 한다 (if 조건문)
  3. 대출 기능을 계속 반복할 수 있도록 while문으로 반복(변수 < 4) 3권을 넘으면 반복문이 끝난다.
  4. rent.txt 파일을 만들고 [폰번호, 제목] 형식으로 저장한다. (대출목록 출력용)
  */
  STD_Mib *pStd_ptr = GET_STD_PTR();
  /*
    printf("핸드폰번호로 회원정보를 조회하세요 : ");
    // mem.txt 문자열비교
    printf(" %s 회원님 반갑습니다.\n");
    printf("대출할 책을 입력해주세요 : ");
    // 대출기능에서 mmap 기능을 가져와서 while반복문 (입력 != 1)
    printf(" %s의 반납이 완료되었습니다.");
    printf("반납을 끝내고 돌아가려면 1을 입력해주세요.");
  */

  int fd;
  void *file_memory;
  char *rent_book[10];
  int rent_mem;
  char *token;
  int i, j;
  int answer;

  // printf("등록 회원 수 : %d\n", pStd_ptr->h_idx); //test code
  // for (int j = 0; j < pStd_ptr->h_idx; j++)
  // {
  //   printf("%s, %s, %s\r\n",
  //          pStd_ptr->MEM_in[j].name,
  //          pStd_ptr->MEM_in[j].phone,
  //          pStd_ptr->MEM_in[j].gene);
  // }
  // printf("대여할 회원의 핸드폰 번호 뒷자리를 입력해 주세요: ");
  // scanf("%d", rent_mem);
  // printf("\n");

  // pStd_ptr->RE[pStd_ptr->r_idx].mem_phon = rent_mem; // 회원번호

  // TODO: book.txt 문자열 비교 -> 1.대출중인책입니다. 2. 대출화면으로

  fd = open(BOOK_FILE_NAME, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  file_memory = mmap(0, FILE_LENGTH, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
  size_t file_size = lseek(fd, 0, SEEK_END);
  int line_cnt;

  if (file_memory == MAP_FAILED)
  {
    perror("mmap");
    exit(1);
  }

  printf("대여할 도서의 제목을 입력해 주세요: ");
  scanf("%s", &rent_book);
  printf("\n");

  // 찾는 조건을 입력하고 해당 줄수를 리턴 받기
  line_cnt = Get_bookfile_line(file_memory, file_size, ELEM_TYPE_TITLE, rent_book);
  // 라인 수를 입력하면 대출여부 변경 설정
  Set_bookfile_rent_stat(file_memory, file_size, line_cnt, '0');
  // printf(" 도서 '%s' 가 대출되었습니다. ", rent_book);

  // unmap and close
  munmap(file_memory, FILE_LENGTH);
  close(fd);

  /*
  // TODO: 대여일자 출력.
  timer = (time_t)time(NULL);
  pStd_ptr->RE[pStd_ptr->r_idx].rent_date = timer;
  pStd_ptr->RE[pStd_ptr->r_idx].due_date = (timer + 259200); // 대여일 3일

  t = localtime(&timer);

  printf("회원번호 %d님, 대여 완료되었습니다.[Date_%d년_%d월_%d일]\n", rent_mem, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
  pStd_ptr->r_idx++;
  */
}

void return_BOOK() // 도서반납 - 회원용
{
  /* TODO:
  1. 회원정보를 입력한다. --> mem.txt 파일에서 해당하는 정보 읽어오기
  2. 반납할책의 목록이 뜬다. --> 해당 핸드폰번호와 매칭하여 for문으로 rent.txt 파일에서 목록을 읽어옴
  3. 반납시 book.txt 인덱스가 변경된다 --> 대출기능의 mmap 가져오기
  4. 반납 기능을 계속 반복할 수 있도록 while문 사용
  +추가) 연체된 경우 알림을 준다.  */
  STD_Mib *pStd_ptr = GET_STD_PTR();
  printf("핸드폰번호로 회원정보를 조회하세요 : ");
  // mem.txt 문자열비교
  printf(" %s 회원님 반갑습니다.\n");
  printf("현재 대출중인 책의 목록입니다.");
  printf("반납할 책이 없습니다."); // NULL
  // rent.txt 파일에서 읽어온다.
  printf("반납할 책을 입력해주세요 : ");
  // 대출기능에서 mmap 기능을 가져와서 while반복문 (입력 != 1)
  printf(" %s 의 반납이 완료되었습니다.");
  printf(" 연체되었습니다. 연체 %d 일\n");
  printf("반납을 끝내고 돌아가려면 1을 입력해주세요.");

  // FILE *rr_fp = fopen(RENT_FILE_NAME, "a");
  // if (rr_fp == NULL)
  // {
  //   printf("%s 파일열기 실패\n", RENT_FILE_NAME);
  // }
  // else
  // {
  //   int re_num1;
  //   int sec;
  //   int late_day;
  //   for (int j = 0; j < pStd_ptr->r_idx; j++)
  //   {
  //     printf("대여번호 : %d/ 책번호 : %d/ 핸드폰번호 : %d/ [대출상태 : %d] ( 0:대여중/ 1:대여가능)\n",
  //            pStd_ptr->RE[j].rent_id,
  //            pStd_ptr->RE[j].book_num1,
  //            pStd_ptr->RE[j].mem_phon,
  //            pStd_ptr->RE[j].b_sta);
  //   }
  //   printf("반납할 도서의 대여번호를 입력해 주세요: ");
  //   scanf("%d", &re_num1);
  //   pStd_ptr->RRE[pStd_ptr->rr_idx].rent_id = pStd_ptr->rr_idx; // 반납번호
  //   pStd_ptr->RRE[pStd_ptr->rr_idx].book_num1 = pStd_ptr->RE[re_num1].book_num1;
  //   pStd_ptr->RRE[re_num1].b_sta = 1;
  //   pStd_ptr->RRE[pStd_ptr->rr_idx].b_sta = 1;
  //   //    pStd_ptr->RRE[pStd_ptr->rr_idx].retu_date = tr = time(NULL); // 반납일자
  //   // 연체된 경우
  //   if (pStd_ptr->RRE[pStd_ptr->rr_idx].retu_date > pStd_ptr->RE[re_num1].due_date)
  //   {
  //     sec = pStd_ptr->RRE[pStd_ptr->rr_idx].retu_date - pStd_ptr->RE[re_num1].due_date;
  //     late_day = ((sec / 86400) + 1); // sec -> day
  //     printf("연체된 책입니다. 연체일수는 %d 일 입니다.", late_day);
  //   }
  //   printf("\n");
  //   printf("책 반납이 완료되었습니다.\n");
  //   fprintf(rr_fp, "\n %d, %d, %d ", pStd_ptr->RRE[pStd_ptr->rr_idx].rent_id, pStd_ptr->RRE[pStd_ptr->rr_idx].book_num1, pStd_ptr->RRE[pStd_ptr->rr_idx].b_sta);
  //   pStd_ptr->rr_idx++;
  //   fclose(rr_fp);
  //}
}

void input_RENT()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  // FILE *r_fp = fopen(RENT_FILE_NAME, "r");
  // if (r_fp == NULL)
  // {
  //   printf("%s 파일열기 실패\n", RENT_FILE_NAME);
  // }
  // else
  // {
  //   char line[150];
  //   char *ptr;
  //   int word_cnt;
  //   // 회원파일 입력
  //   while (fscanf(r_fp, "%s", line) > 0)
  //   {
  //     word_cnt = 0;
  //     ptr = strtok(line, ",");
  //     while (ptr != NULL)
  //     {
  //       word_cnt++;
  //       switch (word_cnt)
  //       {
  //       case 1: // 대여번호
  //         pStd_ptr->RE[pStd_ptr->r_idx].rent_id = atoi(ptr);
  //         break;
  //       case 2: // 도서번호
  //          pStd_ptr->RE[pStd_ptr->r_idx].book_num1 = atoi(ptr);
  //         break;
  //       case 3: // 대여회원의 폰번호
  //         pStd_ptr->RE[pStd_ptr->r_idx].mem_phon = atoi(ptr);
  //         break;
  //       case 4: // 대여 상태
  //         pStd_ptr->RE[pStd_ptr->r_idx].b_sta = atoi(ptr);
  //         break;
  //       }
  //       ptr = strtok(NULL, ",");
  //     }
  //     pStd_ptr->r_idx++;
  //   }
  //   fclose(r_fp);
  // }
}

void input_RETURN()
{
  STD_Mib *pStd_ptr = GET_STD_PTR();
  // FILE *rr_fp = fopen(RENT_FILE_NAME, "r");
  // if (rr_fp == NULL)
  // {
  //   printf("%s 파일열기 실패\n", RENT_FILE_NAME);
  // }
  // else
  // {
  //   char line[150];
  //   char *ptr;
  //   int word_cnt;
  //   // 회원파일 입력
  //   while (fscanf(rr_fp, "%s", line) > 0)
  //   {
  //     word_cnt = 0;
  //     ptr = strtok(line, ",");
  //     while (ptr != NULL)
  //     {
  //       word_cnt++;
  //       switch (word_cnt)
  //       {
  //       case 1: // 대여번호
  //         pStd_ptr->RRE[pStd_ptr->rr_idx].rent_id = atoi(ptr);
  //         break;
  //       case 2: // 도서번호
  //         pStd_ptr->RRE[pStd_ptr->rr_idx].book_num1 = atoi(ptr);
  //         break;
  //       case 3: // 대여회원 폰번호
  //         pStd_ptr->RRE[pStd_ptr->rr_idx].mem_phon = atoi(ptr);
  //         break;
  //       case 4: // 대여 상태
  //         pStd_ptr->RRE[pStd_ptr->rr_idx].b_sta = atoi(ptr);
  //         break;
  //       }
  //       ptr = strtok(NULL, ",");
  //     }
  //     pStd_ptr->r_idx++;
  //   }
  //   fclose(rr_fp);
  // }
}
