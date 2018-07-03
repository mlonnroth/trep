/* Copyright (c) 2018 by Magnus Lonnroth */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Default values for lunch-break and stop-time */
#define DEFAULT_ILUNCH 15
#define DEFAULT_STOP "1600"

/* Convert string-time input (hhmm) to minutes since midnight
   Formula: input is integer-divided by 100 to get hours, then multiplied by 60 to get minutes
   Add input modulo 100 to get remainder in minutes to be added to result */
int atomin (char *time) {
  int foo, hrs, mins;
  foo = atoi(time);
  mins = foo%100;
  hrs = foo/100;
  assert(hrs >= 0 && hrs < 23);
  assert(mins >= 0 && mins < 60);
  return hrs*60+mins;
}

/* Print usage and exit */
#define PROG "trep" 
void usage_exit() {
  printf("Usage:\t%s start [stop] [lunch]\n", PROG);
  puts("\tstart/stop format hhmm");
  puts("\tlunch format mm");
  printf("\n\'%s 745 1615 30\' means you came at 07:45 and left at 16:15 with a 30 minutes lunch\n\n", PROG);
  printf("Default values: if not specified, stop defaults to 1600 and lunch to 15\n(c) 2018 M.Lonnroth\n");
  exit(1);
}

/* Read start- (hhmm) and stop-time (hhmm) and lunch-break (mm) and return working time.
   Stop-time and lunch-break are optional. */
int main (int argc, char **argv) {
  int iwork, istart, istop, ilunch, hrs, mins;
  char sstart[6], sstop[6];

  /* Check that we have at least one parameter for start-time (and max 3 params total) */
  if (argc <= 1 || argc > 4) {
    usage_exit();
  }  
  istart = atomin(argv[1]);

  /* Convert lunch-break to minutes or use default value */
  if (argc < 4 || !argv[3]) {
    ilunch = DEFAULT_ILUNCH;
  } else {
    ilunch = atoi(argv[3]);
  }

  /* Convert stop-time to minutes or use default value */
  if (argc < 3 || !argv[2]) {
    istop = atomin(DEFAULT_STOP);
  } else {
    istop = atomin(argv[2]);
  }

  /* Sanity check input */
  if (istop <= istart) {
    printf("Error: stop (%s = %d) must be after start (%s = %d)\n", argv[1], istop, argv[2], istart);
    usage_exit();
  }
  if (ilunch < 0) {
    printf("Error: lunch (%d) cannot be negative!\n", ilunch);
    usage_exit();
  }

  /* Working time is stop-time minus start-time minus lunch-break */
  iwork = istop - istart - ilunch;

  /* Format and print results */
  sprintf(sstart, "%02d:%02d", istart/60, istart%60);
  sprintf(sstop, "%02d:%02d", istop/60, istop%60);
  printf("Start = %s, stop = %s, lunch = %d\n", sstart, sstop, ilunch);
  hrs = iwork / 60;
  mins = iwork%60;
  printf("Working time: %d hours and %d minutes (lunch %d minutes)\n", hrs, mins, ilunch);
}
