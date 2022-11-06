#include <stdio.h>


/*예시에서 7, 8만봐서는 다른 예시일 경우가 정확하지 않다고 판단했습니다.
ex)가운데 &만늘어나는 방식인지, 아니면 그냥 줄바뀜마다 문자가 바뀌면서 상하좌우가 커지는 것인지 알 수 없기에
줄바뀜마다 문자가 바뀌고 가운데 줄은 무조건 한줄, 모래시계가 상하좌우로 커진다고 가정하고 문제를 해결했습니다. */

int main()
{
    int size; //크기를 나타내는 변수
    printf("크기를 입력하세요: ");
    scanf_s("%d", &size);
    int front = 1; //모래시계의 왼쪽 표시 담당
    int end = size; //모래시계의 오른쪽 표시 담당
    int check = 0; // &, *를 결정하는 변수

    for (int i = 1; i <= size; i++) {
        if (i == 1 || i == size) { //첫줄과 마지막 줄은 *로 꽉채움
            for (int j = 1; j <= size; j++) {
                printf("*");
            }
            if (i == 1 && size % 2 == 0) { //첫줄 이후, 입력크기가 짝수면 한칸 \n을 해줌
                printf("\n");
            }
        }
        else { //그 이외의 줄
            for (int j = 1; j <= size; j++) {
                if (front - 1 == end) { //front와 end가 반전되는 순간, 중간 줄이 2번 생기는걸 방지
                    break;
                }
                else if (j == front || j == end) { //문자 출력이 필요한 순간 제어
                    if (check) { //check가 1경우 &, 0일 경우 *
                        printf("&");
                    }
                    else {
                        printf("*");
                    }
                }
                else { //나머지는 빈칸으로 채움
                    printf(" ");
                }
            }
        }
        if (front - 1 != end) { //front와 end가 중간에 반전되는 순간은 그대로 넘어감
            check = !check; //0이면 1로, 0이면 1으로 반전시켜 다음 줄에 입력될 문자를 변경
            printf("\n");
        }
        front++; //문자 한칸씩 앞으로 전진
        end--; //문자 한칸씩 뒤로 전진
    }

    return 0;
}