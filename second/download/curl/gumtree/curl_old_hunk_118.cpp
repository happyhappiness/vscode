      buffer[iosb.iosb$w_bcnt] = '\0';

    sts = sys$dassgn(chan);
  }
  return buffer; /* we always return success */
}
#else /* VMS */
#ifdef HAVE_TERMIOS_H
#  if !defined(HAVE_TCGETATTR) && !defined(HAVE_TCSETATTR) 
#    undef HAVE_TERMIOS_H
#  endif
#endif

#ifndef RETSIGTYPE
#  define RETSIGTYPE void
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <stdio.h>
#include <signal.h>
#ifdef HAVE_TERMIOS_H
#  include <termios.h>
#else
#  ifdef HAVE_TERMIO_H
#  include <termio.h>
#  else
#  endif
#endif

/* The last #include file should be: */
#if defined(CURLDEBUG) && defined(CURLTOOLDEBUG)
#include "memdebug.h"
#endif

char *getpass_r(const char *prompt, char *buffer, size_t buflen)
{
  FILE *infp;
  char infp_fclose = 0;
  FILE *outfp;
  RETSIGTYPE (*sigint)(int);
#ifdef SIGTSTP
  RETSIGTYPE (*sigtstp)(int);
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
#ifdef SIGTSTP
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
#ifdef SIGTSTP
  signal(SIGTSTP, sigtstp);
#endif

  if(infp_fclose)
    fclose(infp);

  return buffer; /* we always return success */
}
#endif /* VMS */
#else /* WIN32 */
#include <stdio.h>
#include <conio.h>
char *getpass_r(const char *prompt, char *buffer, size_t buflen)
{
  size_t i;
  printf("%s", prompt);
 
  for(i=0; i<buflen; i++) {
    buffer[i] = getch();
    if ( buffer[i] == '\r' ) {
      buffer[i] = 0;
      break;
    }
