# 42cursus_02_minitalk
## 개요
두 가지 유닉스 시그널만을 가지고 서버와 클라이언트간의 메세지 통신 프로그램을 만든다.

## mandatory
* server가 먼저 시작된 다음 PID를 출력해야 한다.  
* client 측에서 parameter로 server의 PID와 전송할 string을 받는다.  
* 클라이언트는 매개변수로 전달된 문자열을 서버에 전달해야 한다. 한 번 문자열이 수신되면 서버는 이를 표시해야 한다.
* UNIX signal만 사용해야 한다.
* 빠르게 출력되어야 한다. (hint: 100자에 1초는 COLOSSAL 하다.)
* 서버는 연속으로 문자열을 받을 수 있어야 한다. 재시작 없이.
* SIGUSR1과 SIGUSR2 두 개의 시그널만 사용할 수 있다.
* 사용가능 함수
  * write, signal, sigemptyset, sigaddset, sigaction, kill, getpid, malloc, free, pause, sleep, usleep, exit
