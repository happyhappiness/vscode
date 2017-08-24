{
  static char rawbuf[FILENAME_MAX+1];
  char *dp = rindex(cp, '/');

  if (dp == 0)
    return 0;

  *dp = 0;
  strcpy(rawbuf, cp);
  *dp = '/';
  strcat(rawbuf, "/r");
  strcat(rawbuf, dp+1);
  return rawbuf;
}