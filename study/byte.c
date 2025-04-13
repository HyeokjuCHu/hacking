#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char * str = "ABCD"; // 16진수: 41424344
	puts(str);	// 문자열 출력 결과: ABCD

    unsigned int num = 0;
    num = 0x41424344;
    printf("%x\n", num);  // 16진수 출력 결과: 41424344
  
    return 0;
}