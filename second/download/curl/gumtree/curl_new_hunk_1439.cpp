  /* 20000318 mgs
   * this is needed by the emx system, SIGTSTP is not a supported signal */
#ifndef __EMX__
  sigtstp = signal(SIGTSTP, SIG_IGN);
#endif

  infp=fopen("/dev/tty", "r");
  if( NULL == infp )
    infp = stdin;
  else
    infp_fclose = 1;

  outfp = stderr;

  infd = fileno(infp);
  outfd = fileno(outfp);

  /* dissable echo */
#ifdef HAVE_TERMIOS_H
  tcgetattr(outfd, &orig);

  noecho = orig;
  noecho.c_lflag &= ~ECHO;
  tcsetattr(outfd, TCSANOW, &noecho);
#else
#  ifdef HAVE_TERMIO_H
  ioctl(outfd, TCGETA, &orig);
  noecho = orig;
  noecho.c_lflag &= ~ECHO;
  ioctl(outfd, TCSETA, &noecho);
#  else
#  endif
#endif

  fputs(prompt, outfp);
  fflush(outfp);
