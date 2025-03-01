CURLcode Curl_getinfo(struct SessionHandle *data, CURLINFO info, ...)
{
  va_list arg;
  long *param_longp=NULL;
  double *param_doublep=NULL;
  char **param_charp=NULL;
  struct curl_slist **param_slistp=NULL;
  int type;
  /* default return code is to error out! */
  CURLcode ret = CURLE_BAD_FUNCTION_ARGUMENT;

  if(!data)
    return ret;

  va_start(arg, info);

  type = CURLINFO_TYPEMASK & (int)info;
  switch(type) {
  case CURLINFO_STRING:
    param_charp = va_arg(arg, char **);
    if(NULL != param_charp)
      ret = getinfo_char(data, info, param_charp);
    break;
  case CURLINFO_LONG:
    param_longp = va_arg(arg, long *);
    if(NULL != param_longp)
      ret = getinfo_long(data, info, param_longp);
    break;
  case CURLINFO_DOUBLE:
    param_doublep = va_arg(arg, double *);
    if(NULL != param_doublep)
      ret = getinfo_double(data, info, param_doublep);
    break;
  case CURLINFO_SLIST:
    param_slistp = va_arg(arg, struct curl_slist **);
    if(NULL != param_slistp)
      ret = getinfo_slist(data, info, param_slistp);
    break;
  default:
    break;
  }

  va_end(arg);
  return ret;
}