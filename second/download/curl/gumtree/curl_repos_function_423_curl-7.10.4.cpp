char *getpass_r(const char *prompt, char *buffer, size_t buflen)
{
  FILE *infp;
  char infp_fclose = 0;
  FILE *outfp;
  RETSIGTYPE (*sigint)();
#ifndef __EMX__
  RETSIGTYPE (*sigtstp)();
#endif
  size_t bytes_read;
  int infd;
  int outfd;
#ifdef HAVE_TERMIOS_H
  struct termios orig;
  struct termios noecho;
#else
#  ifdef HAVE_TERMIO_H
  struct termio orig;
  struct termio noecho;  
#  else
#  endif
#endif

  sigint = signal(SIGINT, SIG_IGN);
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

  bytes_read=read(infd, buffer, buflen);
  buffer[bytes_read > 0 ? (bytes_read -1) : 0] = '\0';

  /* print a new line if needed */
#ifdef HAVE_TERMIOS_H
  fputs("\n", outfp);
#else
#  ifdef HAVE_TERMIO_H
  fputs("\n", outfp);
#  else
#  endif
#endif

  /*
   * reset term charectaristics, use TCSAFLUSH incase the
   * user types more than buflen
   */
#ifdef HAVE_TERMIOS_H
  tcsetattr(outfd, TCSAFLUSH, &orig);
#else
#  ifdef HAVE_TERMIO_H
  ioctl(outfd, TCSETA, &orig);
#  else
#  endif
#endif
  
  signal(SIGINT, sigint);
#ifndef __EMX__
  signal(SIGTSTP, sigtstp);
#endif

  if(infp_fclose)
    fclose(infp);

  return buffer; /* we always return success */
}