#include <stdio.h>
#include <stdlib.h>

void test1()
{
    short t[4] = {1664, -1664, 15, -15};

    for(int k = 0;k<4;k++)
    {
        printf("%d\n", t[k]);
        t[k] += ((short)t[k] >> 15) & 3329;
        printf("%d\n", t[k]);
    }
}

void test2()
{
    unsigned int d0;
    double test_d;
    short origin[4] = {1664, -1664, 15, -15};
    short u;
    short t[4] = {0,0,0,0};
    
    for(int i =3225;i<3329;i++)
    {
        u = i;
        d0 = u << 4;    // 32bit에 12bit를 4bit 왼쪽으로 shift 한 값을 저장
        d0 += 1665;     // 반올림을 위해 q + 2 / 2 값을 더해주기
        
        //d0 *= 80635;    // 
        test_d = d0;
        test_d = test_d / 3329;

        if (test_d >16, test_d<17)
        {
            printf("%d  ", i);
        }
        else{
            break;
        }
        // printf("%f\n", (test_d / 268435456));
        // d0 >>= 28;      // 
        
        // t[i] = d0 & 0xf;
        // printf("%d\n", t[i]);
    }

}

void test2_2()
{
    short t[4] = {1664, -1664, 15, -15};
    
    for(int k = 0;k<4;k++)
    {
        printf("%d\n", t[k]);
        t[k] = t[k] + ((unsigned short)t[k] >> 15);
        printf("%d\n", t[k]);
        t[k] = t[k] & 3329;
        printf("%d\n", t[k]);
    }
}


void test3()
{
    unsigned short t[4] = {1664, -1664, 15, -15};
    
    for(int k = 0;k<4;k++)
    {   
        printf("%d\n", t[k]);
        t[k] = t[k] + (((short)t[k] >> 15)& 3329);
        printf("%d\n", t[k]);
    }
}


//   결국 signed 를 unsigned로 변경하면 자료형의 signed 값을 더한다고 생각하면 됨
//-> 8bit 범위 (-128 ~ 127) -> (0 ~ 255)
void test4()
{
    signed char t[4] = {128, -2, -3, -4};

    for (int i =0;i<4;i++)
    {
        printf("signed t[%d] = %d\n",i, t[i]);
        
        printf("unsigned t[%d] = %d\n", i, (unsigned char)t[i]);
    }

}

void test5()
{
    if(0)
    {
        printf("0\n");
    }
    else{
        printf("not 0\n");
    }
}



void test6()
{
    unsigned int a = 0;
    a = 12 * 256;
    printf("%d\n", a);
    a = a * (1<<12);
    printf("%d\n", a);
    a = a / 8;
    printf("%d\n", a);
    a = a /3329;
    printf("%d\n", a);
    a = a + 168;
    printf("%d\n", a);
    a = a / 168;
    printf("%d\n", a);
    
}

void test7(){
    int i =0 ;
    unsigned short t[20];

    for (i = 0; i < 20; i++) {
        printf("%d\n", i);
        t[i] = i;
        printf("%d\n", t[i]);
    }
    printf("%d\n", i);
     
}

void test8()
{
    int i =0 ;
    int *t_array;
    t_array = (int*)malloc(64);

    for(i = 0;i<32;i++)
    {
        t_array[i] = i;
        printf("%d  ", t_array[i]);
    }

    t_array += 20;

    for(i = 0;i<10;i++)
    {
        t_array[i] = i;
        printf("%d  ", t_array[i]);
    }


    printf("\n\n");
    for(i = 0;i<64;i++)
    {
        printf("%d  ", t_array[i]);
    }

}

#define KYBER_ROOT_OF_UNITY 17
#define KYBER_Q 3329
#define MONT (-1044) // 2^16 mod q
#define QINV (-3327) // q^-1 mod 2^16

#include <stdint.h>



static const uint8_t tree[128] = {
  0, 64, 32, 96, 16, 80, 48, 112, 8, 72, 40, 104, 24, 88, 56, 120,
  4, 68, 36, 100, 20, 84, 52, 116, 12, 76, 44, 108, 28, 92, 60, 124,
  2, 66, 34, 98, 18, 82, 50, 114, 10, 74, 42, 106, 26, 90, 58, 122,
  6, 70, 38, 102, 22, 86, 54, 118, 14, 78, 46, 110, 30, 94, 62, 126,
  1, 65, 33, 97, 17, 81, 49, 113, 9, 73, 41, 105, 25, 89, 57, 121,
  5, 69, 37, 101, 21, 85, 53, 117, 13, 77, 45, 109, 29, 93, 61, 125,
  3, 67, 35, 99, 19, 83, 51, 115, 11, 75, 43, 107, 27, 91, 59, 123,
  7, 71, 39, 103, 23, 87, 55, 119, 15, 79, 47, 111, 31, 95, 63, 127
};

int16_t PQCLEAN_KYBER512_CLEAN_montgomery_reduce(int32_t a)
{
    int16_t t;

    t = (int16_t)a * QINV;
    t = (a - (int32_t)t * KYBER_Q) >> 16;
    return t;
}
int16_t PQCLEAN_KYBER512_CLEAN_barrett_reduce(int16_t a) {
    int16_t t;
    const int16_t v = ((1 << 26) + KYBER_Q / 2) / KYBER_Q;

    t = ((int32_t)v * a + (1 << 25)) >> 26;
    t *= KYBER_Q;
    return a - t;
}
static int16_t fqmul(int16_t a, int16_t b)
{
    return PQCLEAN_KYBER512_CLEAN_montgomery_reduce((int32_t)a * b);
}

void init_ntt() {
  unsigned int i;
  int16_t tmp[128];
  int16_t zetas[128];

  tmp[0] = MONT;
  for(i=1;i<128;i++)
    tmp[i] = fqmul(tmp[i-1],MONT*KYBER_ROOT_OF_UNITY % KYBER_Q);

  for(i=0;i<128;i++) {
    zetas[i] = tmp[tree[i]];
    if(zetas[i] > KYBER_Q/2)
      zetas[i] -= KYBER_Q;
    if(zetas[i] < -KYBER_Q/2)
      zetas[i] += KYBER_Q;
  }
  for(i=0;i<128;i++)
  {
    printf("%d ", zetas[i]);
    if((i + 1) % 8 == 0)
    {
        printf("\n");
    }
  }
}

int main()
{
    init_ntt();

   

    return 0;
}