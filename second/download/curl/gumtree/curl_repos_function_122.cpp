char *getmyhost(char *buf, int buf_size)
{
#if defined(HAVE_GETHOSTNAME)
  gethostname(buf, buf_size);
#elif defined(HAVE_UNAME)
  struct utsname ugnm;
  strncpy(buf, uname(&ugnm) < 0 ? "localhost" : ugnm.nodename, buf_size - 1);
  buf[buf_size - 1] = '\0';
#else
  /* We have no means of finding the local host name! */
  strncpy(buf, "localhost", buf_size);
  buf[buf_size - 1] = '\0';
#endif
  return buf;
}