int set_modtime(char *fname,time_t modtime)
{
#ifdef HAVE_UTIME_H
  struct utimbuf tbuf;  
  tbuf.actime = time(NULL);
  tbuf.modtime = modtime;
  return utime(fname,&tbuf);
#elif defined(HAVE_UTIME)
  time_t t[2];
  t[0] = time(NULL);
  t[1] = modtime;
  return utime(fname,t);
#else
  struct timeval t[2];
  t[0].tv_sec = time(NULL);
  t[0].tv_usec = 0;
  t[1].tv_sec = modtime;
  t[1].tv_usec = 0;
  return utimes(fname,t);
#endif
}