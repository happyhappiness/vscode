cdtime_t cdtime(void) /* {{{ */
{
  int status;
  struct timeval tv = {0, 0};

  status = gettimeofday(&tv, /* struct timezone = */ NULL);
  if (status != 0) {
    char errbuf[1024];
    ERROR("cdtime: gettimeofday failed: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return 0;
  }

  return TIMEVAL_TO_CDTIME_T(&tv);
}