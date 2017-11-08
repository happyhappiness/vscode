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