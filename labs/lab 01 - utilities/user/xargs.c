#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

void xargs(char* base_argv[MAXARG]);

int main(int argc, char* argv[]) {
  if (argc <= 1) {
    fprintf(2, "Usage: xargs [command [initial-arguments]]\n");
    exit(1);
  }

  char* base_argv[MAXARG];
  for (int i = 1; i < argc; ++i) {
    base_argv[i-1] = argv[i];
  } 
  base_argv[argc - 1] = 0;
  xargs(base_argv);
  exit(0);
}

void parse_and_exec(char* base_argv[MAXARG], char unparsed_args[512]) {
  char* argv[MAXARG];
  int i = 0;
  for (; i < MAXARG; ++i) {
    if (base_argv[i] == 0) {
      break;
    }
    argv[i] = base_argv[i];
  }

  int left = 0;
  for (int right = 0; right < 512; ++right) {
    if (unparsed_args[right] == '\0') {
      if (right > left) {
        argv[i] = &unparsed_args[left];
        unparsed_args[right] = '\0';
        ++i;
      }
      break;    
    } else if (unparsed_args[right] == ' ') {
      if (right == left) {
        ++left;
        continue;
      }
      argv[i] = &unparsed_args[left];
      unparsed_args[right] = '\0';
      left = right + 1;
      ++i;
    } 
  }

  argv[i] = 0;
  if (fork() == 0) {
    exec(argv[0], argv);
    fprintf(2, "xargs: exec failed\n");
    exit(1);
  } else {
    wait(0);
  }
}

void xargs(char* base_argv[MAXARG]) {
  char buf[512];
  int i = 0;

  while (read(0, &buf[i], 1) == 1) {
    printf("%s ", buf);
    if (buf[i] == '\n') {
      buf[i] = '\0';
      parse_and_exec(base_argv, buf);
      i = 0;
    } else {
      i++;
    }
  }

}
