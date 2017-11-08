ParameterError str2num(long *val, const char *str)
{
  if(str) {
    char *endptr;
    long num = strtol(str, &endptr, 10);
    if((endptr != str) && (endptr == str + strlen(str))) {
      *val = num;
      return PARAM_OK;  /* Ok */
    }
  }
  return PARAM_BAD_NUMERIC; /* badness */
}