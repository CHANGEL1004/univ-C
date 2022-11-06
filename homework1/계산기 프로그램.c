#include <stdio.h>

int main()
{
    double num1, num2;
    char oper;
    printf("실수를 입력하시오: ");
    scanf_s("%lf", &num1);

    while (1) {
        getchar();
        printf("계산을 입력하시오: ");
        scanf_s("%c", &oper, 1);

        if (oper == 'q') break;

        scanf_s("%lf", &num2);
        switch (oper) 
        {
        case '+':
            num1 += num2;
            printf("%.1lf\n", num1);
            break;
        case '-':
            num1 -= num2;
            printf("%.1lf\n", num1);
            break;
        case '/':
            if (num2 == 0) printf("0으로 나누었으니 다시 입력하시오.\n"); 
            else
            {
                num1 /= num2;
                printf("%.1lf\n", num1);
                break;
            }
        case '*':
            num1 *= num2;
            printf("%.1lf\n", num1);
            break;
        default:
            printf("지원되지 않는 연산자입니다.\n");
            break;
        }
    }

    return 0;
}
