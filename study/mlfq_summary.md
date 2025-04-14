# 💻 운영체제 스케줄링 요약 (Round-Robin ~ MLFQ)
_정리 날짜: 2025-04-14_

## ✅ Round-Robin의 동작 방식
- 프로세스마다 고정된 time quantum 동안만 CPU를 사용
- time quantum이 지나면 다음 프로세스로 교체
- Circular Queue를 사용해 공평하게 돌아가면서 실행
- 남은 시간이 있으면 다시 큐 뒤로 보내져서 계속 실행
- 너무 작으면 context switch 오버헤드 많아짐
- 너무 크면 FCFS처럼 됨 (반응성 ↓)

## ✅ SJF와 Priority Scheduling
- SJF (Shortest Job First)는 평균 waiting time을 최소화 → 가장 효율적
- 하지만 다음 CPU burst 시간을 정확히 예측해야 하므로 실제 사용은 어려움
- Starvation(기아 현상) 발생 가능성 있음
- Priority Scheduling도 같은 단점 존재 → 낮은 priority는 계속 밀릴 수 있음
- Aging 기법을 통해 오래 기다리면 priority를 점점 높여서 starvation을 해결 가능

## ✅ Multilevel Queue Scheduling (MLQ)
- 프로세스를 여러 큐로 나눔 (real-time, system, interactive 등)
- 각 큐는 고정된 우선순위 → 상위 큐가 비지 않으면 하위 큐는 CPU 못 씀
- 큐 간 이동 없음 → 유연성 부족, Starvation 위험 높음
- 각 큐는 서로 다른 알고리즘 사용 가능 (RR, FCFS 등)

## ✅ MLFQ (Multi-Level Feedback Queue)
- MLQ의 단점을 해결하기 위해 큐 간 이동 허용
- 새 프로세스는 항상 최상위 큐(Q0)에서 시작
- CPU 사용 시간 많아지면 점점 낮은 큐로 이동 (demotion)
- 짧게 CPU 쓰거나 I/O 작업 많은 경우 높은 큐에 남음
- 각 큐는 다른 time quantum과 알고리즘을 사용 (보통 Q0: RR 8ms, Q1: RR 16ms, Q2: FCFS)
- 응답성, 공정성, 효율성을 동시에 잡기 위한 전략

## ✅ 선점 여부와 시간 측정
- 새 프로세스가 들어온다고 해서 모든 프로세스가 멈추는 건 아님
- 선점은 새로운 프로세스가 더 높은 priority일 때 발생
- 운영체제는 timer interrupt를 통해 프로세스가 실행되는 동안만 시간 누적
- 시간 초과된 프로세스만 큐 강등 대상이 됨

## ✅ MLFQ 시나리오 예제
- A(5ms): Q0에서 바로 종료
- B(20ms): Q0(8ms) → Q1(12ms) → 종료
- C(40ms): Q0(8ms) → Q1(16ms) → Q2(16ms) → 종료
- 실제 실행 시간에 따라 큐 이동이 결정되며, 대기 중인 프로세스는 시간 계산 X

