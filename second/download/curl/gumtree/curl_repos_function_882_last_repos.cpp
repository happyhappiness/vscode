ParameterError str2num(long *val, const char *str)
{
  if(str) {
    char *endptr;
    long num;
    errno = 0;
    num = strtol(str, &endptr, 10);
    if(errno == ERANGE)
      return PARAM_NUMBER_TOO_LARGE;
    if((endptr != str) && (endptr == str + strlen(str))) {
      *val = num;
      return PARAM_OK;  /* Ok */
    }
  }
  return PARAM_BAD_NUMERIC; /* badness */
}