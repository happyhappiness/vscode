static ParameterError str2double(double *val, const char *str, long max)
{
  if(str) {
    char *endptr;
    double num;
    errno = 0;
    num = strtod(str, &endptr);
    if(errno == ERANGE)
      return PARAM_NUMBER_TOO_LARGE;
    if(num > max) {
      /* too large */
      return PARAM_NUMBER_TOO_LARGE;
    }
    if((endptr != str) && (endptr == str + strlen(str))) {
      *val = num;
      return PARAM_OK;  /* Ok */
    }
  }
  return PARAM_BAD_NUMERIC; /* badness */
}