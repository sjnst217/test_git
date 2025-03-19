#include <stdio.h>

// 사직연산 함수를 만드는데, 개발자1은 덧셈, 뺄셈, 개발자2는 곱셈, 나눗셈, 개발자 3은 최대공약수를 만든다고 가정.
// 각각 다른 branch로 합친다고 하자.

// 개발자 1
double add(double a, double b);
double sub(double a, double b);

// 개발자 2
double mul(double a, double b);
double divi(double a, double b);

// 개발자 3
int gcd(int a, int b);

int gcd(int a, int b)
{
    if(b == 0)
    {
        return a;
    }
    else
    {
        return  gcd(b, (a % b));
    }
}

int main()
{
    double a, b = 0.0;

    a = 14;
    b = 6;

    printf("gcd(%d, %d) = %d", (int)a, (int)b, gcd((int)a, (int)b));

    return 0;
}