#include <stdio.h>

int main()
{
    int front = 0, end = 100;
    int middle = (front + end) / 2;
    int count = 0;
    int check;
    while (front + 1 < end - 1) { //�� �ڵ�� 1���� �������, 98���� Ŭ ��찡 ����� �ٷ� ���������ϴ�. ��, 0�� 99�϶��� �����������Ƿ� ī��Ʈ���� �����߽��ϴ�.
        count++;
        printf("%d���� ������ 0, ������ 1, ũ�� 2�� �Է��Ͻÿ�:", middle);
        scanf_s("\n%d", &check);
        if (check == 0) {
            if (front + 1 == middle) { //�� ���� ī��Ʈ ������ �ʽ��ϴ�.����Ž���� 7������ ��� ���� Ž�� �����ѵ� �̷� ���ܵ� ī��Ʈ���ָ� �ȵȴٰ� �����߽��ϴ�.
                printf("%d���� ū�� %d���� �۴ٴ� ���� ���� �����Դϴ�.\n", front, middle);
                count--;
                continue;
            }
            end = middle;
        }
        else if (check == 1) {
            break;
        }
        else if (check == 2) {
            if (end - 1 == middle) { //�� ���� ī��Ʈ ������ �ʽ��ϴ�.
                printf("%d���� ������ %d���� ũ�ٴ� ���� ���� �����Դϴ�.\n", end, middle);
                count--;
                continue;
            }
            front = middle;
        }
        else {  //�� ���� ī��Ʈ ������ �ʽ��ϴ�.
            printf("0, 1, 2 �߿� �ϳ��� �Է��Ͻÿ�.\n");
            count--;
            continue;
        }
        middle = (front + end) / 2;
    }
    printf("����ڴ� %d�� �����߽��ϴ�. %d�� ���� ���� ������ϴ�.", middle, count);

    return 0;
}