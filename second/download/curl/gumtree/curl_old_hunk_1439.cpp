  /* 20000318 mgs
   * this is needed by the emx system, SIGTSTP is not a supported signal */
#ifndef __EMX__
  sigtstp = signal(SIGTSTP, SIG_IGN);
#endif

  if( (infp=fopen("/dev/tty", "r")) == NULL )
  {
    infp = stdin;
  }
  if( (outfp=fopen("/dev/tty", "w")) == NULL )
  {
    outfp = stderr;
  }
  infd = fileno(infp);
  outfd = fileno(outfp);

  /* dissable echo */
#ifdef HAVE_TERMIOS_H
  if(tcgetattr(outfd, &orig) != 0)
  {
    ; /*perror("tcgetattr");*/
  }
  noecho = orig;
  noecho.c_lflag &= ~ECHO;
  if(tcsetattr(outfd, TCSANOW, &noecho) != 0)
  {
    ; /*perror("tcgetattr");*/
  }
#else
#  ifdef HAVE_TERMIO_H
  if(ioctl(outfd, TCGETA, &orig) != 0)
  {
    ; /*perror("ioctl");*/
  }
  noecho = orig;
  noecho.c_lflag &= ~ECHO;
  if(ioctl(outfd, TCSETA, &noecho) != 0)
  {
    ; /*perror("ioctl");*/
  }
#  else
#  endif
#endif

  fputs(prompt, outfp);
  fflush(outfp);
