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