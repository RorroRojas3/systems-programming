#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int process;
int fuel;

void rang(int signum)
{
  process = 1;
}

int main(int argc, char *argv[])
{
  signal(SIGALRM, rang);
  alarm(1);
  fuel = 10;
  pause();
  while (1)
  {
    if (process == 1 && fuel >= 0)
    {
      process = 0;
      printf("Hello\n");
      fuel--;
      alarm(2);
    }
  }
  return 0;
}
