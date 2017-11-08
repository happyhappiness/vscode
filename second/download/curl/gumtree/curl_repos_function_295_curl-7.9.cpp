char *getpass_r(const char *prompt, char *buffer, size_t buflen)
{
  FILE *infp;
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
  if(tcsetattr(outfd, TCSAFLUSH, &orig) != 0)
  {
    ; /*perror("tcgetattr");*/
  }
#else
#  ifdef HAVE_TERMIO_H
  if(ioctl(outfd, TCSETA, &orig) != 0)
  {
    ; /*perror("ioctl");*/
  }
#  else
#  endif
#endif
  
  signal(SIGINT, sigint);
#ifndef __EMX__
  signal(SIGTSTP, sigtstp);
#endif

  return buffer; /* we always return success */
}