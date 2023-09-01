#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

int main(void) {

  // printf("CHAR_BIT    :   %d\n", CHAR_BIT);
  // printf("CHAR_MAX    :   %d\n", CHAR_MAX);
  // printf("CHAR_MIN    :   %d\n", CHAR_MIN);
  // printf("INT_MAX     :   %d\n", INT_MAX);
  // printf("INT_MIN     :   %d\n", INT_MIN);
  // printf("LONG_MAX    :   %lld\n", (long long) LLONG_MAX);
  // printf("LONG_MIN    :   %lld\n", (long long) LONG_MIN);
  // printf("SCHAR_MAX   :   %d\n", SCHAR_MAX);
  // printf("SCHAR_MIN   :   %d\n", SCHAR_MIN);
  // printf("SHRT_MAX    :   %d\n", SHRT_MAX);
  // printf("SHRT_MIN    :   %d\n", SHRT_MIN);
  // printf("UCHAR_MAX   :   %d\n", UCHAR_MAX);
  // printf("UINT_MAX    :   %u\n", (unsigned int) UINT_MAX);
  // printf("ULONG_MAX   :   %lu\n", (unsigned long) ULONG_MAX);
  // printf("USHRT_MAX   :   %d\n", (unsigned short) USHRT_MAX);


  int a;
  long long aa, b = 12345;
  char *c, d[3], e[6], f[10] = "ola mundo";

  c = "ola mundo";
  sprintf(e, "%05lld", b);
  aa = (b & 00110);
  printf("%lld\n",aa);
  // while(1) {
  //   printf("int: %d\n\n", scanf("%9d", &a));
  //   fflush(stdin);
  //   printf("float: %d\n\n", scanf("%9f", &b));
  //   fflush(stdin);
  //   printf("string: %d\n\n", scanf(" %9[^\n]", c));
  //   fflush(stdin);
  // }
  
  return 0;
}