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

---

# 🛠️ 해킹 관련 리눅스 기초 개념

## 👤 사용자(User)와 그룹(Group)

- **사용자(User)**: 시스템에 로그인할 수 있는 개별 계정 (ex: root, hyeokju)
- **그룹(Group)**: 사용자들을 묶는 단위. 파일 권한을 그룹 단위로 부여할 수 있음.

사용자/그룹 관련 명령어:
```bash
whoami        # 현재 사용자 확인
id            # UID, GID, 그룹 확인
cat /etc/passwd  # 전체 사용자 정보 확인
cat /etc/group   # 전체 그룹 정보 확인
```

---

## 📁 주요 사용자/인증 관련 파일

| 파일 경로 | 설명 |
|-----------|------|
| `/etc/passwd` | 사용자 계정 정보 (로그인 ID, UID, GID, 홈디렉토리, 기본 쉘 등) |
| `/etc/shadow` | 실제 암호화된 비밀번호가 저장된 파일 (읽기 제한) |
| `/etc/group` | 시스템의 그룹 정보 저장 |
| `/etc/sudoers` | sudo 권한 설정 파일 (visudo로 편집 권장) |

비밀번호는 `/etc/passwd`가 아닌 `/etc/shadow`에 해시 형태로 저장되어 있으며, root 또는 sudo 권한만 읽을 수 있음.

## 예시 보기
```bash
cat /etc/passwd | head -n 5
cat /etc/shadow | sudo head -n 5
cat /etc/sudoers  # -> sudo visudo 명령어로 편집 권장
```

## 💡 해커 관점에서 유의할 점
- `/etc/passwd`는 일반 사용자도 읽을 수 있어 사용자 목록 파악에 활용됨
- `/etc/shadow`는 해시된 암호가 저장되어 있어 탈취 후 크랙 시도 가능
- 권한 상승 기법 중 하나가 sudo misconfig 또는 setuid 바이너리 악용

---

## 📂 파일 및 디렉토리 권한 이해

리눅스에서는 각 파일이나 디렉토리에 대해 **소유자(owner)**, **소유 그룹(group)**, 그리고 **기타 사용자(other/world)**에게 **읽기(r)**, **쓰기(w)**, **실행(x)** 권한을 각각 줄 수 있음.

예시 출력:
```
-rwxrwxr-x 2 user user 4096 12월 2 13:38 dir
```

- 세 번째 열: 파일/디렉토리의 **소유자** → `user`
- 네 번째 열: 해당 파일의 **소유 그룹** → `user`
- 첫 번째 열: 권한 정보
  - `-` : 일반 파일 (디렉토리는 `d`)
  - `rwx` : 소유자 권한 (read, write, execute)
  - `rwx` : 그룹 권한
  - `r-x` : 기타 사용자 권한

예시:
```
-rwxrw-r-- 1 user user 13122 12월 2 13:08 world
```
- **소유자**: user → `rwx` (읽기/쓰기/실행 가능)
- **소유 그룹**: user → `rw-` (읽기/쓰기 가능)
- **기타 사용자**: world → `r--` (읽기만 가능)

## 권한 요약

| 구분 | 의미 |
|------|------|
| `r` | read (읽기) |
| `w` | write (쓰기) |
| `x` | execute (실행) |
| `-` | 해당 권한 없음 |

## 참고 명령어
```bash
ls -l           # 권한, 소유자, 소유 그룹 확인
chmod +x file   # 실행 권한 추가
chmod 755 file  # 숫자 기반 권한 설정
chown user file # 소유자 변경
chgrp group file # 소유 그룹 변경
```

권한은 해킹 시에 매우 중요함. 실행 권한이 있는 파일은 악성 코드 삽입 또는 권한 상승에 사용될 수 있으며, world 권한이 과하게 열려 있으면 정보 유출 위험이 커짐.

