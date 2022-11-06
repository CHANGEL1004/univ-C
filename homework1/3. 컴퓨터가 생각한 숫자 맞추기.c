#include <stdio.h>

int main()
{
    int front = 0, end = 100;
    int middle = (front + end) / 2;
    int count = 0;
    int check;
    while (front + 1 < end - 1) { //이 코드는 1보다 작을경우, 98보다 클 경우가 생기면 바로 끝내버립니다. 즉, 0과 99일때는 비교하지않으므로 카운트에서 제외했습니다.
        count++;
        printf("%d보다 작으면 0, 같으면 1, 크면 2를 입력하시오:", middle);
        scanf_s("\n%d", &check);
        if (check == 0) {
            if (front + 1 == middle) { //이 경우는 카운트 해주지 않습니다.이진탐색은 7번내로 모든 수가 탐색 가능한데 이런 예외도 카운트해주면 안된다고 생각했습니다.
                printf("%d보다 큰데 %d보다 작다는 것은 논리적 오류입니다.\n", front, middle);
                count--;
                continue;
            }
            end = middle;
        }
        else if (check == 1) {
            break;
        }
        else if (check == 2) {
            if (end - 1 == middle) { //이 경우는 카운트 해주지 않습니다.
                printf("%d보다 작은데 %d보다 크다는 것은 논리적 오류입니다.\n", end, middle);
                count--;
                continue;
            }
            front = middle;
        }
        else {  //이 경우는 카운트 해주지 않습니다.
            printf("0, 1, 2 중에 하나만 입력하시오.\n");
            count--;
            continue;
        }
        middle = (front + end) / 2;
    }
    printf("사용자는 %d를 생각했습니다. %d번 만에 답을 맞췄습니다.", middle, count);

    return 0;
}