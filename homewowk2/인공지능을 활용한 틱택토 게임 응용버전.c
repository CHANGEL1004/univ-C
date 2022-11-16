#include <stdio.h>

int weight[3][3]; //가중치 배열
int a[8] = { 0, 0, 1, 1, 1, -1, -1, -1}; // 놓은 자리의 주위를 탐색하기 위한 배열 a, b
int b[8] = { 1, -1, 0, 1, -1, 0, 1, -1}; //
int x, y; //사용자가 입력한 자리
int mi, mj; //컴퓨터가 선택한 자리

//공격 및 방어를 위한 계산을 해주는 함수(다음 턴에 이기거나 질 수 있는 경우)
void pair_case(char board[][3], int value, int xx, int yy, char check) {

   //모든 경우에서 weight[?][?] < 900 의미는 이미 놓여져 있는 자리에는 다시 둘 수 없으니 가중치 계산이 무의미 하다는 것을 의미한다.
   //한줄에서 한 칸을 띄고 두개가 존재하는 경우 (O O 이런식으로 놓여있는걸 의미함)
   for (int i = 0; i < 3; i++) {
      if ((board[i][0] == check) && (board[i][2] == check) && (weight[i][1] < 900)) {
         weight[i][1] -= value;
      }
      if ((board[0][i] == check) && (board[2][i] == check) && (weight[1][i] < 900)) {
         weight[1][i] -= value;
      }
   }
   if ((board[0][0] == check) && (board[2][2] == check) && (weight[1][1] < 900)) {
      weight[1][1] -= value;
   }
   if ((board[0][2] == check) && (board[2][0] == check) && (weight[1][1] < 900)) {
      weight[1][1] -= value;
   }

   //한줄에서 2개가 붙어있는 경우
   for (int i = 0; i < 3; i++) {
      if ((board[i][0] == check) && (board[i][1] == check) && (weight[i][2] < 900)) {
         weight[i][2] -= value;
      }
      if ((board[0][i] == check) && (board[1][i] == check) && (weight[2][i] < 900)) {
         weight[2][i] -= value;
      }
      if ((board[i][1] == check) && (board[i][2] == check) && (weight[i][0] < 900)) {
         weight[i][0] -= value;
      }
      if ((board[1][i] == check) && (board[2][i] == check) && (weight[0][i] < 900)) {
         weight[0][i] -= value;
      }
   }
   if ((board[0][0] == check) && (board[1][1] == check) && (weight[2][2] < 900)) {
      weight[2][2] -= value;
   }
   if ((board[1][1] == check) && (board[2][2] == check) && (weight[0][0] < 900)) {
      weight[0][0] -= value;
   }
   if ((board[0][2] == check) && (board[1][1] == check) && (weight[2][0] < 900)) {
      weight[2][0] -= value;
   }
   if ((board[2][0] == check) && (board[1][1] == check) && (weight[0][2] < 900)) {
      weight[0][2] -= value;
   }
}

//가중치를 계산하는 함수
void plus_minus_weight(int xx, int yy, int value) {
   weight[xx][yy] = 999;
   for (int j = 0; j < 8; j++) {
      if (xx + a[j] >= 0 && xx + a[j] < 3 && yy + b[j] >= 0 && yy + b[j] < 3) {
         weight[xx + a[j]][yy + b[j]] += value;

         //오목에 쌍삼이 있듯이 택택토에도 특수한 경우가 존재한다. 그걸 막기위해서 각 모서리의 가중치를 좀더 비중있게 하였다. ()
         if (xx + a[j] == yy + b[j]) weight[xx + a[j]][yy + b[j]] += value;
         if ((xx + a[j] == 0 && yy + b[j] == 2) || (xx + a[j] == 2 && yy + b[j] == 0)) weight[xx + a[j]][yy + b[j]] += value;
      }
   }
}

//컴퓨터가 놓는 함수
/*좀 더 설명하자면 가중치가 가장 작을 경우를 컴퓨터가 찾아서 수를 놓도록 설계했다. 평소에는 방어를 하되, 무조건 이길 수 있는 기회가 오면 승리를 하도록 설계하였다.
컴퓨터가 무조건 이길 수 있는 경우는 가중치를 100빼주고 유저가 무조건 이길 수 있는 경우는 가중치를 50빼주었다. 수치에 딱히 공식은 없으며 그냥
상하관계를 명백히 하기위한 수치로 적당히 설정하였다.*/
void computer_turn(char board[][3], int k) {
   int min = 999; //여기서 999는 inf랑 비슷한 의미로 사용하였다. 틱택토는 턴이 적어서 너무 큰 수를 사용하지 않아도 된다고 생각했다,

   plus_minus_weight(x, y, -1); /*일단 사용자가 놓은 자리 주변은 가중치를 1 빼준다. 크게 의미는 없는 수치지만 일단 1개 놓여져 있더라도 어느정도 위험도는 있으니까
                        이렇게 설정하였다.*/
   if (k == 1 && board[1][1] == ' ') { //첫 턴에 중앙이 비어있다면 무조건 중앙에 놓도록했다. 중앙을 거쳐 3개가 되는 경우의 수가 압도적으로 많기 때문에 이 부분만 따로 떼어주었다.
      mi = 1;
      mj = 1;
   }
   else { //첫 턴을 제외한 상태
      pair_case(board, 50, x, y, 'O'); //일단 O는 유저의 수이다. 유저의 수를 막아야 하는 경우는 가중치에서 50을 빼주었다.
      pair_case(board, 100, mi, mj, 'X'); //X는 컴퓨터의 수이다. 이기는 걸 최우선으로 하기위해 이길 수 있는 경우는 가중치에서 100을 빼주었다.
      for (int i = 0; i < 3; i++) { //이제 가중치가 가장 작은 자리가 컴퓨터의 다음 수가 된다.
         for (int j = 0; j < 3; j++) {
            if (min > weight[i][j]) {
               min = weight[i][j];
               mi = i;
               mj = j;
            }
         }
      }
   }
   plus_minus_weight(mi, mj, 1); //컴퓨터가 놓은 자리 주변 가중치를 1 더해준다. 후공이므로 내가 2개를 이어봤자 상대가 더 빨리 이었을 가능성이 크다, 그렇기에 차별을 두기위해 1을 더해줬다.
   printf("%d %d \n", mi, mj);
   board[mi][mj] = 'X'; //위에서 계산한 좌표에 X를 놓는다.
}

char check_win(char board[][3]) {
   //삼단논법을 활용! (A는 B다. B는 C다. 그럼 A=B=C다.)
   for (int i = 0; i < 3; i++) { //행 검사
      if ((board[i][0] == board[i][1]) && (board[i][1] == board[i][2])) {
         return board[i][0];
      }
   }
   for (int i = 0; i < 3; i++) { //열 검사
      if ((board[0][i] == board[1][i]) && (board[1][i] == board[2][i])) {
         return board[0][i];
      }
   }
   if ((board[0][0] == board[1][1]) && (board[1][1] == board[2][2])) //대각선 검사
      return board[0][0];
   else if ((board[0][2] == board[1][1]) && (board[1][1] == board[2][0]))
      return board[0][2];
   return ' '; //아무것도 해당되지 않을시 공백 리턴
}
int main(void)
{
   char board[3][3];
   // 보드를 초기화한다.
   for (x = 0; x < 3; x++)
      for (y = 0; y < 3; y++) board[x][y] = ' ';
   // 사용자로부터 위치를 받아서 보드에 표시한다.
   for (int k = 0; k < 9; k++) {
      while (1) {
         if (k % 2 == 0) {
            printf("사용자의 차례 (x, y) 좌표: ");
            scanf_s("%d %d", &x, &y);
            if ((x >= 3 || x < 0) || y >= 3 || y < 0) {
               printf("판에서 벗어났습니다!\n\n");
               continue;
            }
            else {
               if (board[x][y] != ' ') {
                  printf("이미 입력된 자리입니다!\n\n");
                  continue;
               }
               else {
                  board[x][y] = 'O';
                  break;
               }
            }
         }
         else {
            printf("컴퓨터의 차례 (x, y) 좌표: ");
            computer_turn(board, k);
            break;
         }
      }
      // 보드를 화면에 그린다.
      for (int i = 0; i < 3; i++) {
         printf("---|---|---\n");
         printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
      }
      printf("---|---|---\n\n");

      if (k >= 4) { //자신의 턴 기준으로 3번째 돌아오는 턴부터 승리가능 (3개는 놓아야하니까)
         if (check_win(board) == 'O') {
            printf("인간이 이겼습니다.\n");
            break;
         }
         else if (check_win(board) == 'X') {
            printf("컴퓨터가 이겼습니다.\n");
            break;
         }
      }

      if (k == 8) printf("비겼습니다.\n"); //위의 if문에서 8까지 걸러지지 않는다면 비긴것
   }
   return 0;
}
