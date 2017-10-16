  if(ftpcode)
    *ftpcode=code; /* return the initial number like this */

  return nread; /* total amount of bytes read */
}

/* -- who are we? -- */
static char *getmyhost(char *buf, int buf_size)
{
#if defined(HAVE_GETHOSTNAME)
  gethostname(buf, buf_size);
#elif defined(HAVE_UNAME)
  struct utsname ugnm;
  strncpy(buf, uname(&ugnm) < 0 ? "localhost" : ugnm.nodename, buf_size - 1);
