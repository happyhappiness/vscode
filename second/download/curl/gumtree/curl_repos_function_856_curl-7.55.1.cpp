ParameterError str2offset(curl_off_t *val, const char *str)
{
  char *endptr;
  if(str[0] == '-')
    /* offsets aren't negative, this indicates weird input */
    return PARAM_NEGATIVE_NUMERIC;

#if(CURL_SIZEOF_CURL_OFF_T > CURL_SIZEOF_LONG)
  *val = curlx_strtoofft(str, &endptr, 0);
  if((*val == CURL_OFF_T_MAX || *val == CURL_OFF_T_MIN) && (errno == ERANGE))
    return PARAM_NUMBER_TOO_LARGE;
#else
  errno = 0;
  *val = strtol(str, &endptr, 0);
  if((*val == LONG_MIN || *val == LONG_MAX) && errno == ERANGE)
    return PARAM_NUMBER_TOO_LARGE;
#endif
  if((endptr != str) && (endptr == str + strlen(str)))
    return PARAM_OK;

  return PARAM_BAD_NUMERIC;
}