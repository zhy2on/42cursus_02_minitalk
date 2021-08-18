
# 42cursus_02_minitalk
## 개요
두 가지 유닉스 시그널만을 가지고 서버와 클라이언트간의 메세지 통신 프로그램을 만든다.

## Mandatory
* server가 먼저 시작된 다음 PID를 출력해야 한다.  
* client 측에서 parameter로 server의 PID와 전송할 string을 받는다.  
* 클라이언트는 매개변수로 전달된 문자열을 서버에 전달해야 한다. 한 번 문자열이 수신되면 서버는 이를 표시해야 한다.
* UNIX signal만 사용해야 한다.
* 빠르게 출력되어야 한다. (hint: 100자에 1초는 COLOSSAL 하다.)
* 서버는 연속으로 문자열을 받을 수 있어야 한다. 재시작 없이.
* SIGUSR1과 SIGUSR2 두 개의 시그널만 사용할 수 있다.
* 사용가능 함수
  * write, signal, sigemptyset, sigaddset, sigaction, kill, getpid, malloc, free, pause, sleep, usleep, exit

## Bonus
* 작은 수신 확인 시스템 추가
* 유니코드 지원

## 자료 정리
### write

```c
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count);
```

* 파일 쓰기 함수. fd에 있는 내용을 count만큼 buf에 담는다.  
* 리턴값: 성공시 전달한 바이트 수, 실패시 -1

### signal

```c
#include <signal.h>

typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
```

* signal이란 software interrput로 process에 무언가 발생했음을 알리는 간단한 메세지를 비동기적으로 보내는 것이다.
* signum은 시그널을 발생시키는 번호. 해당 시그널의 시그넘이 발생하면 handler를 실행하는 것.

### sigemptyset

```c
 #include <signal.h>

int sigemptyset(sigset_t *set);
```

* https://reakwon.tistory.com/53
* https://kcoder.tistory.com/entry/%EC%8B%9C%EA%B7%B8%EB%84%90-%EC%8B%9C%EA%B7%B8%EB%84%90-%EC%A7%91%ED%95%A9signal-set-%EC%B2%98%EB%A6%AC
* sigset_t 라는 집합에 모든 시그널을 추가하거나 모든 시그널을 제거한다.
* 리턴값: 성공시 0, 실패시 -1

### sigaddset

```c
 #include <signal.h>

int sigaddset(sigset_t *set, int signo);
```

* sigset에 signal을 추가하거나 삭제한다.
* 리턴값: 성공시 0, 실패시 -1

### sigaction

```c
#include <signal.h>

int sigaction(int signum, const struct sigaction *restrict act,
                   struct sigaction *restrict oldact);
```

* https://velog.io/@two_jay/sigaction
* signal함수보다 조금 더 다양한 기능을 지원하는 시그널 함수다.
* 처리할 시그널의 signum, 시그널을 처리할 방법을 지정한 구조체 주소 act, 기존에 시그널을 처리하던 방법을 저장할 구조체 주소 oldact
* 리턴값: 성공시 0, 실패시 -1

### sigaction 구조체

```c
struct sigaction {
    void (*sa_handler)(int);    // signal 핸들러 함수
    void (*sa_sigaction)(int, siginfo_t *, void *);
    // 밑의 sa_flags가 SA_SIGINFO일때 sa_handler 대신에 동작하는 핸들러
    sigset_t sa_mask;             // 시그널 처리시 블록 지정할 시그널 마스크
    int sa_flags;                // sig_flag 기능 지정을 위한 상수
    void (*sa_restorer)(void);  // 응용프로그램 코드에서는 사용하지 말자.
}
```

* https://velog.io/@two_jay/sigaction

### PID
* Process IDentifier. 프로세스 식별자. 유닉스 커널과 같은 운영체제에서 각 프로세스나 서비스를 식별하기 위해 할당하는 고유 번호.
* 프로세스 ID는 프로세스가 생성된 순서대로 번호를 순차적으로 할당한다. 먼저 실행된 프로세스가 종료되었다고 해서 비어있는 PID를 사용하지 않는다.
* 그리고 할당할 수 있는 최대 PID에 도달하면 다시 1번부터 사용하지 않는 PID를 찾아서 할당해간다.


### kill

```c
#include <signal.h>

int kill(pid_t pid, int sig);
```

* PID에 signal 전송.
  
| PID | 의미 |
|-----|-----|
|양의 정수|지정한 PID에 시그널 전송|
|0|함수를 호출하는 프로세스와 같은 그룹에 있는 모든 프로세스에 시그널 전송|
|-1|함수를 호출하는 프로세스가 전송할 수 있는 권한을 가진 모든 프로세스에 시그널 전송|
|-1 이외의 음수|첫 번째 인수 PID의 절댓값 프로세스 그룹에 속하는 모든 프로세스에 시그널 전송|

* 리턴값: 성공시 0, 실패시 -1

### getpid

```c
#include <unistd.h>

pid_t getpid(void);
pid_t getppid(void);
```

* 실행중인 PID를 구한다.
* 리턴값: 현재 프로세스의 ID

### malloc


```c
 #include <stdlib.h>

void *malloc(size_t size);
```

* 프로그램 실행중에 동적으로 메모리를 할당하는 함수.
* Heap 영역에 할당한다.

### free

```c
 #include <stdlib.h>

void free(void *ptr);
```

* 메모리 해제 함수.
* malloc으로 생성 했던 메모리 영역을 해제한다.

### pause

```c
#include <unistd.h>

int pause(void);
```

* 시그널을 수신할 때까지 대기(실행을 중단)하는 함수.
* 리턴값: 이 함수는 시그널을 수신할 때까지 무한히 대기하므로 성공에 대한 반환 값이 존재하지 않는다. 그렇지 않다면 -1을 반환하고 errno에 오류값을 설정한다.

### sleep

```c
#include <unistd.h>

unsigned int sleep(unsigned int seconds);
```

* 일정 시간 동안 프로세스를 대기하게 하는 함수. (초단위)
* 리턴값: 요구된 시간이 경과한 경우 0, 중간에 중단된 경우 남은 시간량(초단위)

### usleep

```c
#include <unistd.h>

int usleep(useconds_t usec);
```

* 일정 시간 동안 프로세스를 대기하게 하는 함수. (마이크로초 단위)
* 마이크로초 = 1/1000000(100만분의 1초)
* 성공시 0, 실패시 -1

### exit

```c
#include <stdlib.h>

void exit(int status);
```

* 정상적으로 프로세스를 종료하는 함수
* 비정상적으로 종료할 때는 abort함수를 사용한다.
* status: 호스트 환경에게 알려 줄 종료 값


## 참조
https://www.geeksforgeeks.org/signals-c-set-2/  

https://opensource.com/article/19/4/interprocess-communication-linux-networking  

