# Main Memory Summary

## 📌 Background

- 프로그램은 실행 전에 디스크에서 메인 메모리(RAM)로 로드되어야 한다.
- CPU가 직접 접근할 수 있는 저장장치는 **메인 메모리와 레지스터**뿐이다.
- 메모리 유닛은 단순히 **주소와 요청(read/write)**만 처리한다.
- 레지스터 접근은 한 클럭 이내로 매우 빠르지만, 메인 메모리는 느려서 **CPU가 대기(stall)**하는 경우가 생긴다.
- 이 속도 차이를 줄이기 위해 **캐시 메모리(Cache)**가 사용된다.
- 올바른 동작을 위해 **메모리 보호**가 필요하다.

---

## 🛡️ Basic Hardware (메모리 보호)

- 각 프로세스는 **독립된 메모리 공간**을 갖는다.
- 이를 위해 **Base Register**와 **Limit Register**를 사용하여 접근 범위를 제한한다.
- CPU는 메모리 접근 시 **주소가 base 이상이고 base + limit 미만**인지 항상 검사한다.
- 조건을 만족하지 않으면 **운영체제에 트랩(trap)**되어 오류 처리한다.
- Base/Limit 레지스터는 **운영체제만 수정 가능(특권 명령)**하다.

---

## 🧭 Logical vs. Physical Address

- **Logical Address (논리 주소)**: CPU가 생성하는 주소, 사용자 프로그램이 보는 주소.
- **Physical Address (물리 주소)**: 실제 메모리 주소, 메모리 유닛이 보는 주소.
- **MMU (Memory Management Unit)**: 실행 중에 논리 주소를 물리 주소로 변환하는 하드웨어.

---

## 🧮 Address Mapping using Relocation Register

- 간단한 주소 변환 방식으로 **Relocation Register (Base Register)** 사용.
- 논리 주소에 relocation 값을 더해 물리 주소로 변환:
  - `physical = logical + base`
- 사용자 프로그램은 **논리 주소만 알고**, 실제 물리 주소는 보지 못함.

---

## 🧠 Why CPU doesn’t add base directly?

- **유연성**: 여러 프로세스마다 base 값이 달라지므로 MMU가 동적으로 처리하는 게 효율적.
- **보안**: 사용자 프로그램이 물리 주소를 알지 못하게 보호.
- **추상화**: 프로세스는 항상 자기 주소 공간만 다루도록 설계됨.
- **이식성**: 어디에 로딩되든 코드 수정 없이 실행 가능.

---

## 🧩 Dynamic Loading

- 프로그램 전체를 한꺼번에 메모리에 올리면 **물리 메모리 크기 제한**이 문제됨.
- **동적 로딩(Dynamic Loading)**은 **필요한 루틴만 실행 중에 로딩**한다.
  - 루틴이 호출되기 전까지 메모리에 없음
  - 호출 시 로딩, 주소 테이블 갱신, 실행
- **장점**:
  - 사용하지 않는 루틴은 메모리에 올라오지 않음 → 메모리 효율적 사용
  - 운영체제의 특별한 지원 없이도 가능 (다만, 라이브러리 제공 등으로 보완 가능)

---

## 🔗 Dynamic Linking

- **Static Linking**: 컴파일 시 라이브러리 코드를 실행 파일에 포함.
- **Dynamic Linking**: **실행 중에** 필요한 라이브러리를 연결.
  - 라이브러리를 가리키는 작은 코드 조각인 **stub**이 먼저 존재.
  - 처음 호출 시 stub이 라이브러리를 메모리에 로드하고 주소를 찾음.
  - 그 다음부터는 stub이 **자기 자신을 진짜 함수 주소로 바꿈** (재배치).
- **장점**:
  - 라이브러리를 **여러 프로세스가 공유**
  - **업데이트가 쉬움** (라이브러리만 바꾸면 됨)
- **운영체제의 지원 필요** (동적 링커 등)

---

## 📚 Dynamic Loading vs Dynamic Linking

| 구분             | Dynamic Loading                        | Dynamic Linking                         |
|------------------|----------------------------------------|-----------------------------------------|
| 대상             | 루틴 또는 코드 전체                    | 주로 라이브러리 함수                    |
| 로딩 시점        | 호출될 때 코드 로딩                    | 호출될 때 링크 진행                    |
| 주소 갱신 방식   | 주소 테이블을 갱신                     | stub이 실제 함수 주소로 교체           |
| 목적             | 메모리 절약                            | 라이브러리 공유, 유지보수 편의성       |

---

## ✅ 요약

> 메인 메모리는 CPU와 프로그램 간의 핵심 연결고리다.  
> 논리 주소와 물리 주소의 분리, 보호 기법(Base/Limit),  
> 그리고 실행 시 필요한 것만 불러오는 **동적 로딩/링킹** 덕분에  
> 컴퓨터는 효율적이고 안전하게 여러 프로그램을 실행할 수 있다.

# Main Memory: Contiguous Allocation to Fragmentation Remedies

## 📦 Contiguous Memory Allocation
- 메인 메모리는 OS와 사용자 프로세스를 모두 수용해야 함.
  - 제한된 자원이므로 효율적 할당 필요
- **Contiguous Allocation**은 초기 메모리 관리 방식 중 하나
  - 하나의 프로세스는 하나의 연속된 메모리 블록에 배치됨
- 보통 두 파티션으로 나뉨:
  - OS: 메모리 상단 (high memory)
  - 사용자 프로세스: 메모리 하단 (low memory)
- 제한: 외부 단편화 발생, 연속된 공간이 없으면 프로세스 수용 불가

---

## 📐 Variable Partition
- **가변 크기 파티션(Variable Partition)**: 프로세스 크기에 맞게 메모리를 유동적으로 나눔
- 프로세스가 종료되면 그 자리는 **hole (빈 공간)**으로 남음
- 인접한 hole끼리 합칠 수 있음 (hole merging)
- OS는 다음 정보를 관리함:
  - 어떤 공간이 이미 할당됐는지 (allocated partitions)
  - 어떤 공간이 비어 있는지 (holes)

### 🔧 단점: 외부 단편화 발생
- 충분한 전체 메모리는 있지만, 조각나 있어서 큰 프로세스를 넣을 수 없음
- 이를 **External Fragmentation**이라 함

---

## 📊 Dynamic Storage Allocation Strategies
### 1. **First-fit**
- 가장 먼저 조건에 맞는 hole에 배치
- 빠르지만 앞쪽에 단편화가 많이 생길 수 있음

### 2. **Best-fit**
- 들어갈 수 있는 hole 중 가장 작은 것 선택
- 공간은 절약되지만 탐색 시간이 오래 걸리고 너무 작은 조각이 남을 수 있음

### 3. **Worst-fit**
- 가장 큰 hole을 선택
- 이론상 큰 leftover 공간이 남지만 실제로는 비효율적

### 🔍 결론
- 일반적으로 **First-fit** > **Best-fit** >> **Worst-fit**

---

## 💥 Fragmentation 종류

### 🔷 External Fragmentation
- 총 빈 공간은 충분하지만 **연속된 공간이 없어서** 할당 불가
- 예: 10KB + 8KB + 20KB = 38KB가 있어도 30KB 프로세스를 못 넣는 경우
- **50% Rule**: N개의 프로세스를 할당하면 약 0.5N 개의 hole이 생겨서 메모리 1/3이 낭비될 수 있음

### 🔶 Internal Fragmentation
- 할당된 메모리 블록 중 **일부가 사용되지 않는 낭비**
- 주로 고정 블록 기반 시스템(Paging 등)에서 발생
- 예: 요청 18,462 bytes, 할당 18,464 bytes → 2 bytes 낭비

---

## 🛠 Fragmentation 해결 방법

### 1. **Compaction (압축)**
- 프로세스들을 한쪽으로 몰아붙여 연속된 공간 확보
- 주소 재배치가 필요하므로 비용이 크고 실행 중에만 가능 (동적 재배치 시스템 필요)

### 2. **Paging / Segmentation**
- 프로세스의 논리 주소 공간이 **물리적으로 연속되지 않아도 되도록 허용**
-
#### 📘 Paging:
- 메모리와 프로세스를 일정한 크기의 **page/frame** 단위로 나눔
- 논리 페이지를 물리 프레임으로 매핑함 (Page Table 사용)
- 외부 단편화 없음, 내부 단편화는 일부 존재할 수 있음

#### 📘 Segmentation:
- 주소 공간을 의미 단위로 나눔 (코드, 스택, 데이터 등)
- 논리적으로는 연속되지만, 물리적으로는 흩어져도 됨

---

## ✅ 요약
- 초기에는 **Contiguous Allocation**으로 메모리 할당
- 이후 **Variable Partition**으로 유연성 확보
- 하지만 **외부 단편화** 문제 발생 → 해결 위해 **Compaction** 또는 **Paging/Segmentation** 사용
- Paging은 고정 크기 블록, Segmentation은 의미 단위로 나눔

# Paging부터 Shared Pages까지 정리

## 1. Paging이란?
- **Paging**: 가상 주소 공간을 고정된 크기의 블록(=Page)으로 나누고, 이를 물리 메모리의 고정된 블록(=Frame)에 매핑하는 메모리 관리 기법
- **Logical Address (논리 주소)**: CPU가 생성하는 주소 → (Page number, Offset)으로 구성
- **Physical Address (물리 주소)**: 실제 RAM에서의 주소
- **MMU (Memory Management Unit)**: 논리 주소를 물리 주소로 매핑해주는 하드웨어 장치

## 2. Page Table
- 프로세스마다 자신만의 **Page Table**이 있음
- 각 entry는 해당 Page가 어떤 Frame에 매핑되는지를 기록
- Page Table Entry(PTE)는 다음과 같은 정보 포함:
  - Frame number
  - Valid/Invalid bit
  - Protection bits (읽기/쓰기/실행 권한 등)

## 3. Valid-Invalid Bit
- **Valid bit**: 해당 page가 실제 사용 중 → 접근 가능
- **Invalid bit**: 아직 메모리에 없거나, 접근해서는 안 되는 페이지
- 초기에는 대부분 앞부분만 valid, 나머지는 invalid
- invalid page에 접근 시 → Page Fault 발생 → OS 개입

## 4. Protection Bits
- 각 frame 혹은 PTE마다 접근 권한을 지정 가능
- 예: Read-only, Read-Write, Execute-only 등
- 잘못된 접근 시 H/W trap 발생 → 보호 기능

## 5. Page Table 최적화 장치
- **PTBR**: Page Table의 시작 주소 저장
- **PTLR**: Page Table의 길이 (몇 개의 page를 쓰는지)
- 대부분의 프로세스는 전체 주소 공간을 쓰지 않으므로 PTLR로 낭비 방지

## 6. TLB (Translation Lookaside Buffer)
- **TLB**: 자주 쓰는 Page Table entry를 저장하는 고속 캐시
- 구조: (Page number, Frame number)의 key-value 쌍
- TLB hit: 빠르게 frame 찾기 가능
- TLB miss: Page Table 접근 → TLB에 insert
- 성능 공식:
  ```
  EAT = hit_ratio x 1 access + miss_ratio x 2 accesses
  ```
- TLB는 entry 수 제한 있음 (보통 64~1024개)

## 7. 왜 TLB를 무한정 크게 만들 수 없는가?
- 커질수록 병렬 검색 성능이 떨어짐
- 전력 소비, 발열, 회로 복잡도 증가
- 대신 multi-level TLB, superpage 등 최적화 사용

## 8. Page가 Invalid인 이유
- 전체 논리 주소 공간은 넓지만, 실제 사용하는 page는 일부
- 나머지는 invalid로 표시해서 보호하거나 지연 로딩
- 예: 아직 접근하지 않은 힙/스택 공간 등

## 9. Shared Pages
- **Shared Code**: 여러 프로세스가 같은 읽기 전용(reentrant) 코드 페이지를 공유
  - 예: libc, text editor, 컴파일러 등
  - 조건: read-only + 같은 바이너리 파일
- **Private Code/Data**: 각 프로세스만이 사용하는 고유한 코드/데이터 (heap, stack 등)

## 10. Shared Pages 동작 방식
- 프로세스는 각각 자신만의 Page Table을 가짐
- 하지만 같은 코드(libc 등)의 page는 동일한 물리 메모리 frame을 가리키게 설정
- OS는 파일 경로 + inode 정보 등을 기준으로 "같은 코드"인지 판단
- 수정 후 다시 컴파일한 바이너리는 기존 것과 공유되지 않음 (내용 다름)

## 11. Shared Pages 예시
- 여러 프로세스가 libc1 ~ libc4를 사용하는 경우
- 각자의 Page Table에는 같은 Frame 번호가 적혀 있음
- 실제 물리 메모리에는 libc1 ~ libc4가 한 번만 로딩됨

---

## 12. Structure of the Page Table
- 32bit 주소 공간에서 페이지 크기가 4KB인 경우, 총 2^20개의 페이지 필요 → Page Table에 100만 개의 entry 필요
- 각 entry가 4 bytes일 경우 → Page Table 크기 = 4MB
- 이 크기를 줄이기 위해 다음과 같은 방식 도입:
  - Hierarchical Page Table
  - Hashed Page Table
  - Inverted Page Table

## 13. Hierarchical Page Table
- Page Table을 계층적으로 나눠서 관리 (ex. Two-level Paging)
- 논리 주소 구조: `[p1 | p2 | d]`
  - `p1`: outer page table index
  - `p2`: inner page table index
  - `d`: offset (페이지 내 위치)
- 주소 변환:
  1. p1로 outer table 접근 → inner table 주소 획득
  2. p2로 inner table 접근 → frame number 획득
  3. frame + d → physical address 완성

## 14. Hierarchical Paging in 64-bit Systems
- 64bit 주소공간 = 너무 커서 2단계로 부족
- 예: page size = 4KB일 때 2^52개의 페이지 필요
- 따라서 4단계 또는 5단계 계층 구조 사용 (ex. x86-64: PML4 → PDPT → Page Directory → Page Table)
- 예시 주소: `[p1 | p2 | p3 | d]`
  - p1: 32bit, p2: 10bit, p3: 10bit, d: 12bit → 총 64bit

## 15. Hashed Page Table
- 주로 64bit 이상의 시스템에서 사용
- 페이지 번호(p)를 해시 함수에 넣어 해시 테이블에 매핑
- 충돌을 고려해 연결 리스트 구조 사용
- 각 entry 구성: `(virtual page number, frame number, pointer)`
- 주소 변환:
  1. p → hash function → index
  2. index에서 연결 리스트 탐색
  3. 일치하는 p 찾으면 frame 반환

## 16. Inverted Page Table
- 시스템 전체에 딱 하나의 Page Table 존재
- 기존 방식과 반대로, **물리 프레임 중심으로 관리**
- 각 entry는 실제 메모리 프레임 하나를 대표하며, 다음 정보 저장:
  - (process id, virtual page number)
- 논리 주소: (process id, page number, offset)
- 주소 변환:
  1. inverted table에서 (pid, page number) 검색
  2. 찾으면 해당 프레임 index + offset → physical address 완성

---

> 이 구조들을 통해 OS는 메모리 낭비를 줄이고,  
> 다양한 주소 공간 크기에 유연하게 대응할 수 있다.

