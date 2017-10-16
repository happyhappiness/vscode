      buffer[iosb.iosb$w_bcnt] = '\0';

    sts = sys$dassgn(chan);
  }
  return buffer; /* we always return success */
}
#define DONE
#endif /* VMS */

#ifdef WIN32
/* Windows implementation */
#include <conio.h>
char *getpass_r(const char *prompt, char *buffer, size_t buflen)
{
  size_t i;
  fputs(prompt, stderr);

  for(i=0; i<buflen; i++) {
    buffer[i] = getch();
    if ( buffer[i] == '\r' ) {
      buffer[i] = 0;
      break;
    }
