static int str2num(long *val, char *str)
{
  int retcode = 0;
  if(isdigit((int)*str))
    *val = atoi(str);
  else
    retcode = 1; /* badness */
  return retcode;
}