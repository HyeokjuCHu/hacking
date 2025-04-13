// Name: chall.c
// Compile Option: gcc chall.c -o chall -fno-stack-protector

#include <stdio.h> //기본 입출력
#include <stdlib.h> //동적 메모리 할당
#include <fcntl.h> //파일 디스크립터 오픈 옵션
#include <unistd.h> //read, write 등 저수준 입출력
#include <string.h> // 문자열 처리

#define FLAG_SIZE 0x45 //플래그 최대 크기

void init() { //버퍼 설정; 버퍼링을 비활성한 것. 입/출력 즉시 반응
	setvbuf(stdin, 0, 2, 0); //표준 입력을 라인 버퍼로 설정 X
	setvbuf(stdout, 0, 2, 0);   //표준 출력을 라인 버퍼 없음
}

int main(void) {
    int fd;
    char *flag;

    init(); //위에서 정의한 버퍼 초기화 호출

    // read flag
    flag = (char *)malloc(FLAG_SIZE); //flag 포인터를 flag_Size만큼 동적메모리 할당
    fd = open("./flag", O_RDONLY); //파일 읽기 전용 실패하면 fd==-1이 될것.
    read(fd, flag, FLAG_SIZE); //fd에서 flag_size만큼 읽어서 flag에 저장. 플래그 내용을 메모리로 읽어옴.

    char cmp_str[10] = "Dreamhack";
    char inp_str[10];   
    printf("Enter \"Dreamhack\" : ");
    scanf("%9s", inp_str);

    if(strcmp(cmp_str, inp_str) == 0){
        puts("Welcome Beginners!");
        // print flag
        puts(flag);
    }
    
    return 0;
}