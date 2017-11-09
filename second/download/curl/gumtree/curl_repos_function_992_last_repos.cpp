static bool ttyecho(bool enable, int fd)
{
#ifdef struct_term
  static struct_term withecho;
  static struct_term noecho;
#endif
  if(!enable) {
    /* disable echo by extracting the current 'withecho' mode and remove the
       ECHO bit and set back the struct */
#ifdef HAVE_TERMIOS_H
    tcgetattr(fd, &withecho);
    noecho = withecho;
    noecho.c_lflag &= ~ECHO;
    tcsetattr(fd, TCSANOW, &noecho);
#elif defined(HAVE_TERMIO_H)
    ioctl(fd, TCGETA, &withecho);
    noecho = withecho;
    noecho.c_lflag &= ~ECHO;
    ioctl(fd, TCSETA, &noecho);
#else
    /* neither HAVE_TERMIO_H nor HAVE_TERMIOS_H, we can't disable echo! */
    (void)fd;
    return FALSE; /* not disabled */
#endif
    return TRUE; /* disabled */
  }
  /* re-enable echo, assumes we disabled it before (and set the structs we
     now use to reset the terminal status) */
#ifdef HAVE_TERMIOS_H
  tcsetattr(fd, TCSAFLUSH, &withecho);
#elif defined(HAVE_TERMIO_H)
  ioctl(fd, TCSETA, &withecho);
#else
  return FALSE; /* not enabled */
#endif
  return TRUE; /* enabled */
}