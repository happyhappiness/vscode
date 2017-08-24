         mtm->tm_mday, mtm->tm_hour, mtm->tm_min, mtm->tm_year + 1900);
#endif

  printf(" %s", th_get_pathname(t));

#if !defined(_WIN32) || defined(__CYGWIN__)
  if (TH_ISSYM(t) || TH_ISLNK(t))
