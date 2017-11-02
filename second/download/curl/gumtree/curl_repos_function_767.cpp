ParameterError str2unum(long *val, const char *str)
{
  ParameterError result = str2num(val, str);
  if(result != PARAM_OK)
    return result;
  if(*val < 0)
    return PARAM_NEGATIVE_NUMERIC;

  return PARAM_OK;
}