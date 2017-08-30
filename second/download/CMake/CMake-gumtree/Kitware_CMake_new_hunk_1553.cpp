

  printf(" %s", th_get_pathname(t));



#if !defined(_WIN32) || defined(__CYGWIN__)

  if (TH_ISSYM(t) || TH_ISLNK(t))

  {

    if (TH_ISSYM(t))
