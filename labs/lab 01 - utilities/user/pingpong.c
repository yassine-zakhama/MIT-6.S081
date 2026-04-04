#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
  int p[2];
  pipe(p);

  if (fork() == 0) {
    char buff[5];
    read(p[0], buff, 5);
    close(p[0]);
    printf("%d: received %s\n", getpid(), buff);
    write(p[1], "pong", 5);
    close(p[1]);
  } else {
    write(p[1], "ping", 5);
    close(p[1]);
    wait(0);
    char buff[5];
    read(p[0], buff, 5);
    printf("%d: received %s\n", getpid(), buff);
    close(p[0]);
  }

  exit(0);
}
