# 🧠 Linux Virtual Memory (OSTEP 기반 심화 요약)

---

## 1. 가상 메모리의 3대 목적

- **투명성 (Transparency)**  
  - 프로세스마다 독립적인 주소 공간 제공  
  - 연속된 메모리처럼 보이도록 시스템이 매핑 관리

- **보호 (Protection)**  
  - 프로세스 간 메모리 접근 제한  
  - 커널 ↔ 유저 공간 분리 (페이지 보호 비트 사용)

- **효율성 (Efficiency)**  
  - 페이징 단위로 메모리 관리  
  - 스왑, 페이지 교체 정책 등으로 메모리 자원 최적화

---

## 2. 주소 공간(Address Space) 구조

- **유저 공간**
  - 텍스트(코드), 데이터, 힙, 공유 라이브러리, 스택
  - 힙: 낮은 주소 → 높은 주소 성장 (`malloc`)
  - 스택: 높은 주소 → 낮은 주소 성장 (`함수 호출`)

- **커널 공간**
  - 유저 공간에서 접근 불가
  - 시스템 코드, 드라이버, 페이지 테이블 등 포함

---

## 3. 주소 변환 및 하드웨어 지원

- **MMU (Memory Management Unit)**  
  - 가상 주소 → 물리 주소 변환을 하드웨어에서 처리

- **페이지 테이블 (Page Table)**  
  - VPN (Virtual Page Number) ↔ PFN (Physical Frame Number)  
  - **다단계 페이지 테이블 (Multi-level)**  
    - PML4 → PDPT → PD → PT → Frame (x86-64)

- **TLB (Translation Lookaside Buffer)**  
  - 최근 주소 변환 결과 캐싱  
  - TLB miss 시 페이지 테이블 접근

---

## 4. 페이지 폴트와 스왑

- **페이지 폴트 (Page Fault)**  
  - 필요한 페이지가 메모리에 없을 때 발생  
  - Demand Paging에 의해 일반적

- **Swap (스왑 공간)**  
  - 메모리가 부족하면 일부 페이지를 디스크로 내보냄  
  - Swap-in / Swap-out 과정 포함

- **페이지 교체 알고리즘**  
  - FIFO, LRU, Clock 등  
  - 리눅스는 **Clock-Pro (LRU 변형)** 사용

- **스래싱 (Thrashing)**  
  - 페이지 교체가 과도하게 발생하여 성능 급감

---

## 5. 리눅스 가상 메모리의 특징

- **메모리 매핑 (Memory Mapping)**  
  - 실행 파일, 공유 라이브러리, 파일, 익명 메모리 등을 주소 공간에 매핑  
  - `mmap()` 사용

- **copy-on-write (COW)**  
  - `fork()` 후 부모-자식이 메모리 공유  
  - 쓰기 시점에만 복사 발생

- **ASLR (Address Space Layout Randomization)**  
  - 주소 공간 무작위화로 보안 강화

- **Memory cgroup**  
  - 프로세스 그룹 별 메모리 사용 제한 (Docker, LXC 등에서 활용)

---

## 6. 실제 주소 공간 예시

`/proc/<pid>/maps` 예시:

00400000-00452000 r-xp 00000000 08:01 523624 /bin/bash
00651000-00652000 r--p 00051000 08:01 523624 /bin/bash
7f6b2f6ee000-7f6b2f8ae000 r-xp 00000000 08:01 131187 /lib/x86_64-linux-gnu/libc-2.31.so
7ffc3fd5d000-7ffc3fd7e000 rw-p 00000000 00:00 0 [stack]


- `r-xp`: 읽기/실행/비공유 가능
- `[stack]`, `[heap]`, `[anon]`: 익명 메모리 등 표시

---

## 7. 시스템 콜과 메모리 인터페이스

- `brk`, `sbrk`: 힙 공간 확장  
- `mmap`, `munmap`: 파일 또는 익명 메모리 매핑  
- `mprotect`: 페이지 보호 속성 변경 (R/W/X)  

---

## ✅ 결론 요약

- 리눅스 가상 메모리는 **투명성, 보호, 효율성**이라는 세 가지 목표 달성을 위해 설계됨
- **MMU, 페이지 테이블, TLB, 스왑** 등 다양한 기술이 협력
- **보안**: ASLR, 보호 비트, COW  
- **성능 최적화**: 다단계 페이지 테이블, TLB 캐시, 페이지 교체 정책  
- 실제 메모리 맵은 `/proc/[pid]/maps` 또는 `pmap` 명령어로 확인 가능
