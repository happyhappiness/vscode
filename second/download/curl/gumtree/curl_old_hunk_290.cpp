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
    else
      if ( buffer[i] == '\b')
        /* remove this letter and if this is not the first key, remove the
           previous one as well */
        i = i - (i>=1?2:1);
  }
  /* since echo is disabled, print a newline */
  fputs("\n", stderr);
  /* if user didn't hit ENTER, terminate buffer */
  if (i==buflen)
    buffer[buflen-1]=0;

  return buffer; /* we always return success */
}
#define DONE
#endif /* WIN32 */

#ifdef NETWARE
/* NetWare implementation */
#ifdef __NOVELL_LIBC__
#include <screen.h>
char *getpass_r(const char *prompt, char *buffer, size_t buflen)
