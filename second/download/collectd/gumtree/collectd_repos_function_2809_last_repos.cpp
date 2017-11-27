static int get_utc_time(cdtime_t t, struct tm *t_tm, long *nsec) /* {{{ */
{
  struct timespec t_spec = CDTIME_T_TO_TIMESPEC(t);
  NORMALIZE_TIMESPEC(t_spec);

  if (gmtime_r(&t_spec.tv_sec, t_tm) == NULL) {
    char errbuf[1024];
    int status = errno;
    ERROR("get_utc_time: gmtime_r failed: %s",
          sstrerror(status, errbuf, sizeof(errbuf)));
    return status;
  }

  *nsec = t_spec.tv_nsec;
  return 0;
}