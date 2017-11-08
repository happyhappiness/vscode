ParameterError str2double(double *val, const char *str)
{
  if(str) {
    char *endptr;
    double num = strtod(str, &endptr);
    if((endptr != str) && (endptr == str + strlen(str))) {
      *val = num;
      return PARAM_OK;  /* Ok */
    }
  }
  return PARAM_BAD_NUMERIC; /* badness */
}