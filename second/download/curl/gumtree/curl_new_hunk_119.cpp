  /* if user didn't hit ENTER, terminate buffer */
  if (i==buflen)
    buffer[buflen-1]=0;

  return buffer; /* we always return success */
}
#define DONE
#endif /* WIN32 */

#ifndef DONE /* not previously provided */

#ifdef HAVE_TERMIOS_H
#define struct_term struct termios
#else
#ifdef HAVE_TERMIO_H
#define struct_term  struct termio
#else
#undef struct_term
#endif
#endif

static bool ttyecho(bool enable, int fd)
{
#ifdef struct_term
  static struct_term withecho;
  static struct_term noecho;
#endif
  if(!enable) {
  /* dissable echo by extracting the current 'withecho' mode and remove the
     ECHO bit and set back the struct */
#ifdef HAVE_TERMIOS_H
    tcgetattr(fd, &withecho);
    noecho = withecho;
    noecho.c_lflag &= ~ECHO;
    tcsetattr(fd, TCSANOW, &noecho);
#else /* HAVE_TERMIOS_H */
#ifdef HAVE_TERMIO_H
    ioctl(fd, TCGETA, &withecho);
    noecho = withecho;
    noecho.c_lflag &= ~ECHO;
    ioctl(fd, TCSETA, &noecho);
#else /* HAVE_TERMIO_H */
/* neither HAVE_TERMIO_H nor HAVE_TERMIOS_H, we can't disable echo! */
    (void)fd; /* prevent compiler warning on unused variable */
    return FALSE; /* not disabled */
#endif
#endif
    return TRUE; /* disabled */
  }
  else {
    /* re-enable echo, assumes we disabled it before (and set the structs we
       now use to reset the terminal status) */
#ifdef HAVE_TERMIOS_H
    tcsetattr(fd, TCSAFLUSH, &withecho);
#else /* HAVE_TERMIOS_H */
#ifdef HAVE_TERMIO_H
    ioctl(fd, TCSETA, &withecho);
#else
/* neither HAVE_TERMIO_H nor HAVE_TERMIOS_H */
    return FALSE; /* not enabled */
#endif
#endif
    return TRUE; /* enabled */
  }
}

char *getpass_r(const char *prompt, /* prompt to display */
                char *password,     /* buffer to store password in */
                size_t buflen)      /* size of buffer to store password in */
{
  ssize_t nread;
  bool disabled;
  int fd=open("/dev/tty", O_RDONLY);
  if(-1 == fd)
    fd = 1; /* use stdin if the tty couldn't be used */

  disabled = ttyecho(FALSE, fd); /* disable terminal echo */

  fputs(prompt, stderr);
  nread=read(fd, password, buflen);
  if(nread > 0)
    password[--nread]=0; /* zero terminate where enter is stored */
  else
    password[0]=0; /* got nothing */

  if(disabled) {
    /* if echo actually was disabled, add a newline */
    fputs("\n", stderr);
    ttyecho(TRUE, fd); /* enable echo */
  }

  if(1 != fd)
    close(fd);

  return password; /* return pointer to buffer */
}

#endif /* DONE */
#endif /* HAVE_GETPASS_R */
