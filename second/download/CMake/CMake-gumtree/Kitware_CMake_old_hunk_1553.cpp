
  printf(" %s", th_get_pathname(t));

#ifndef _WIN32
  if (TH_ISSYM(t) || TH_ISLNK(t))
  {
    if (TH_ISSYM(t))