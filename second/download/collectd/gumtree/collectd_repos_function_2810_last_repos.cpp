static int get_local_time(cdtime_t t, struct tm *t_tm, long *nsec) /* {{{ */
{
  struct timespec t_spec = CDTIME_T_TO_TIMESPEC(t);
  NORMALIZE_TIMESPEC(t_spec);

  if (localtime_r(&t_spec.tv_sec, t_tm) == NULL) {
    char errbuf[1024];
    int status = errno;
    ERROR("get_local_time: localtime_r failed: %s",
          sstrerror(status, errbuf, sizeof(errbuf)));
    return status;
  }

  *nsec = t_spec.tv_nsec;
  return 0;
}