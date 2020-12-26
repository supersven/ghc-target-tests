/*
 * Copied from aclocal.m4.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

static volatile int tock = 0;
static void handler(int i)
{
   tock = 1;
}

static void timeout(int i)
{
  // timer_settime() has been known to hang, so just in case
  // we install a 1-second timeout (see #2257)
  exit(99);
}

int main(int argc, char *argv[])
{

    struct sigevent ev;
    timer_t timer;
    struct itimerspec it;
    struct sigaction action;
    int m,n,count = 0;

    ev.sigev_notify = SIGEV_SIGNAL;
    ev.sigev_signo  = SIGVTALRM;

    action.sa_handler = handler;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    if (sigaction(SIGVTALRM, &action, NULL) == -1) {
        fprintf(stderr,"SIGVTALRM problem\n");
        exit(3);
    }

    action.sa_handler = timeout;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    if (sigaction(SIGALRM, &action, NULL) == -1) {
      fprintf(stderr,"SIGALRM problem\n");
      exit(3);
    }
    alarm(1);

    if (timer_create(CLOCK_REALTIME, &ev, &timer) != 0) {
        fprintf(stderr,"No CLOCK_REALTIME timer\n");
        exit(2);
    }

    tock = 0;

    it.it_value.tv_sec = 0;
    it.it_value.tv_nsec = 1000000; // 1ms
    it.it_interval = it.it_value;
    if (timer_settime(timer, 0, &it, NULL) != 0) {
        fprintf(stderr,"settime problem\n");
        exit(4);
    }

    // some environments have coarse scheduler/timer granularity of ~10ms and worse
    usleep(100000); // 100ms

    if (!tock) {
        fprintf(stderr,"no CLOCK_REALTIME signal\n");
        exit(5);
    }

    timer_delete(timer);

    exit(0);
}
