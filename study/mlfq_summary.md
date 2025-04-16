# 💻 운영체제 스케줄링 & IPC 통합 정리 (혁주)
_정리 날짜: 2025-04-14_

## 📦 IPC (Inter-Process Communication)
- 단방향 파이프: 한 쪽은 write, 다른 한 쪽은 read만 가능
- 양방향 통신은 파이프 두 개 필요 (ex: 부모→자식, 자식→부모)
- named pipe는 파일처럼 동작하며 양쪽에서 읽고 쓸 수 있음
- fork 이후 파이프는 복사되므로 양쪽에서 FD 조작 가능
- write는 파이프에 데이터를 쓰고, read는 그 데이터를 읽음 (버퍼 기반 통신)
- 부모가 write하면 자식이 read로 consume, 그 반대도 가능

## 🧠 Shared Memory
- pipe는 '터널' 같은 직접 연결 구조, shared memory는 '휴게소'처럼 모두가 접근 가능한 메모리
- 성능은 좋지만 동기화 문제 있음 (mutex, semaphore 등 필요)
- shm_open, mmap 등으로 메모리 공유 가능
- 사용 후 shm_unlink로 제거 (자동 제거 실패 시 수동 처리)

## ⚙️ 프로세스 상태 전이 및 PCB
- Ready → Running → Waiting/Terminated 등 상태 전이
- Ready Queue = 실행 준비된 프로세스 대기 줄 (Priority Queue 구조도 가능)
- PCB(Process Control Block): 프로세스 정보를 저장하는 자료구조
- dispatch latency: context switch 시 필요한 시간 → 작을수록 빠르지만 too frequent switches는 오히려 비효율

## 🧮 CPU Scheduling Algorithms 요약
- FCFS: First Come First Served, 단순하지만 평균 대기시간 길어짐
- SJF: Shortest Job First → 평균 waiting time 최소화. but 다음 burst time 예측 어려움
- Priority Scheduling: 높은 우선순위 먼저. starvation 문제 있음
- RR: Round-Robin → time quantum 기반 선점형 스케줄링. 공정성 good, 오버헤드 주의

## 🔥 Round-Robin 심화
- 각 프로세스는 time quantum만큼 실행됨
- quantum 너무 작으면 context switch 오버헤드 많아짐
- 너무 크면 반응성 떨어져서 FCFS처럼 동작함
- 공정성은 있지만 효율성과 응답성 사이에서 밸런스 필요

## 📊 SJF와 Priority Scheduling 심화
- SJF는 이론상 효율성 최고. 평균 대기시간 최소
- 문제는 burst time 예측 어려움 + starvation
- Priority Scheduling도 동일 문제 존재
- 해결책: Aging (기다린 만큼 우선순위 증가)

## 🏗️ Multilevel Queue (MLQ)
- 프로세스를 고정된 큐로 분리 (real-time, system, batch 등)
- 각 큐는 독립적으로 운영되고 다른 스케줄링 사용 가능
- Fixed-Priority 방식 → starvation 가능성 있음
- Time-Slice 방식 → CPU 시간을 비율로 분배하여 공정성 확보
- 단점: 큐 간 이동 불가 → 유연성 없음

## 🚀 MLFQ (Multilevel Feedback Queue)
- MLQ에 유연성 추가 → 큐 간 이동 허용
- 새 프로세스는 항상 Q0부터 시작
- 많이 실행되면 점점 아래로 내려가고, 짧게 쓰면 위에 유지됨
- 높은 큐는 작은 time quantum + RR, 낮은 큐는 긴 time quantum or FCFS
- Starvation 방지를 위한 aging 기법 내장
- 실행 시간만 누적되어 큐 이동 판단 (대기 시간은 무관)
- 선점 발생: 더 높은 priority 프로세스가 도착하면 현재 실행 프로세스 중단 가능

## 🎬 MLFQ 예제 시뮬레이션
- 프로세스 A(5ms): Q0에서 바로 종료
- 프로세스 B(20ms): Q0(8ms) → Q1(12ms)
- 프로세스 C(40ms): Q0(8ms) → Q1(16ms) → Q2(16ms)
- 실행 시간 기준으로만 큐 이동 결정됨. 대기 중에는 시간 측정 X

