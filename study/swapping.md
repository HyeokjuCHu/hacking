# Swapping 정리

## 1. Swapping이란?
- 프로세스를 메모리에서 디스크(Backing Store)로 "스왑 아웃(Swap-Out)"하고,
  다시 메모리로 "스왑 인(Swap-In)"하여 실행을 이어가는 메모리 관리 기법
- 메모리보다 더 많은 프로세스를 동시에 유지할 수 있도록 해줌

## 2. Swapping vs Paging
| 항목 | Swapping | Paging |
|------|----------|--------|
| 단위 | 전체 프로세스 | 개별 페이지 |
| 디스크 전송 | 프로세스 전체를 보냄 | 필요한 페이지만 보냄 |
| 유연성 | 낮음 | 높음 |
| 속도 | 느림 | 비교적 빠름 |
| 메모리 활용 | 연속 공간 필요 | 비연속 공간 가능 |

## 3. Context Switch + Swapping
- 프로세스 전환 시 다음 프로세스가 메모리에 없으면:
  1. 현재 프로세스 스왑 아웃
  2. 다음 프로세스 스왑 인
- 예시:
  - 프로세스 크기: 100MB
  - 디스크 속도: 50MB/s
  - 전환 시간: 2초 + 2초 = 4초 (4000ms)

## 4. 현대 OS에서 Swapping
- 전통적인 Swapping은 거의 사용되지 않음 (느림, 부담 큼)
- 하지만 **수정된 형태의 Swapping**은 존재함
  - 보통은 Swapping 꺼져 있음
  - 메모리 부족할 때 일시적으로 Swapping 켜짐
  - 다시 여유가 생기면 Swapping 끔
- 예시: UNIX, Linux, Windows

## 5. Swapping with Paging
- Paging 시스템에서는 전체가 아닌 **페이지 단위로 스왑** 가능
- 메모리 부족 시 필요한 페이지만 디스크로 내보내거나 불러옴
- 더 유연하고 빠름

## 6. Mobile 시스템에서 Swapping
- 보통 사용하지 않음 (Flash memory 한계 때문)
  - 저장 공간 작음
  - 쓰기 횟수 제한
  - 느린 I/O 속도
- 대신 다른 방식으로 처리:
  - iOS: 앱에게 메모리 반환 요청, 안 하면 종료
  - Android: 앱 상태를 flash에 저장하고 종료 → 빠른 재시작
- 둘 다 Paging은 지원함

## ✅ 결론
- Swapping은 메모리 초과 문제를 해결하기 위한 고전적인 방식
- 현대 시스템은 Swapping 대신 **Demand Paging, Working Set** 개념을 사용하여 더 효율적으로 메모리 관리

