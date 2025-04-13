# 🐧 Linux 정리

---

## 📌 리눅스란?

- 유닉스(UNIX)를 기반으로 만든 오픈소스 운영체제 커널
- 리누스 토발즈(Linus Torvalds)가 개발 시작 (1991)
- 누구나 자유롭게 수정, 배포 가능 → 다양한 배포판 존재 (Ubuntu, Debian, Kali, CentOS 등)
- 주로 서버, 클라우드, 해킹/보안, 개발 환경에 널리 사용됨

---

## 🖥️ 기본 명령어

| 명령어 | 설명 |
|--------|------|
| ls     | 현재 디렉토리의 파일/폴더 목록 보기 |
| cd     | 디렉토리 이동 |
| pwd    | 현재 위치 출력 |
| mkdir  | 새 폴더 만들기 |
| rm     | 파일/디렉토리 삭제 |
| cp     | 파일 복사 |
| mv     | 파일 이동 또는 이름 변경 |
| cat    | 파일 내용 출력 |
| touch  | 빈 파일 생성 |
| echo   | 문자열 출력 또는 파일에 쓰기 |
| man    | 명령어 설명서 보기 |

## 예시

```bash
cd /home
mkdir test
cd test
touch hello.txt
echo "Hello, Linux" > hello.txt
cat hello.txt
```

---

## 🔍 파일 및 디렉토리 탐색

| 명령어    | 설명                             |
|-----------|----------------------------------|
| find      | 파일/디렉토리 검색               |
| locate    | 인덱스 기반 빠른 검색            |
| grep      | 파일 내 문자열 검색              |
| which     | 명령어 실행 파일 경로 확인       |
| whereis   | 실행파일, 소스, 매뉴얼 위치 확인 |

## 예시

```bash
find /etc -name "*.conf"
grep -rn "127.0.0.1" .
which python3
whereis bash
```

---

## 🌐 네트워크 관련 명령어

| 명령어    | 설명                             |
|-----------|----------------------------------|
| ip a      | IP 주소 확인                     |
| ping      | 네트워크 연결 확인               |
| netstat   | 열려 있는 포트 확인              |
| ss        | netstat 대체 명령어              |
| curl/wget | 웹 리소스 다운로드               |
| scp       | SSH 기반 파일 복사               |
| ssh       | 원격 접속                         |

## 예시

```bash
ping google.com
ssh user@192.168.0.10
scp file.txt user@192.168.0.10:/home/user/
```

---

## 📦 패키지 관리 (APT)

| 명령어        | 설명                         |
|---------------|------------------------------|
| apt update    | 패키지 목록 갱신             |
| apt upgrade   | 설치된 패키지 업그레이드     |
| apt install   | 패키지 설치                  |
| apt remove    | 패키지 삭제                  |
| apt search    | 패키지 검색                  |
| dpkg -i       | .deb 파일 직접 설치          |

## 예시

```bash
sudo apt update && sudo apt upgrade -y
sudo apt install nmap
dpkg -i ./package.deb
```

---

## 📊 시스템 정보 확인

| 명령어    | 설명                         |
|-----------|------------------------------|
| uname -a  | 시스템 커널 정보             |
| df -h     | 디스크 용량 확인             |
| du -sh *  | 디렉토리별 용량 확인         |
| free -h   | 메모리 사용량 확인           |
| uptime    | 시스템 가동 시간             |
| top/htop  | 실시간 프로세스 상태 확인    |

---

## 🧪 실습 예시

```bash
# 사용자 생성 및 권한 부여
sudo adduser hacker
sudo usermod -aG sudo hacker
su - hacker

# 특정 크기 이상의 파일 찾기
find / -type f -size +10M

# 열려 있는 포트 보기
ss -tuln

# sudo 그룹 확인
grep "sudo" /etc/group
```

---

## 🔥 리눅스 꿀팁 모음

| 명령어/단축키 | 설명                         |
|---------------|------------------------------|
| !!            | 직전 명령 재실행             |
| sudo !!       | 직전 명령을 sudo로 실행      |
| Ctrl + R      | 명령어 히스토리 검색         |
| history       | 명령어 기록 보기             |
| alias         | 명령어 단축 설정             |

## 예시

```bash
alias ll='ls -alF'
alias gs='git status'
```

