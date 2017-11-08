CURLcode Curl_getinfo(struct Curl_easy *data, CURLINFO info, ...)
{
  va_list arg;
  long *param_longp = NULL;
  double *param_doublep = NULL;
  curl_off_t *param_offt = NULL;
  const char **param_charp = NULL;
  struct curl_slist **param_slistp = NULL;
  curl_socket_t *param_socketp = NULL;
  int type;
  CURLcode result = CURLE_UNKNOWN_OPTION;

  if(!data)
    return result;

  va_start(arg, info);

  type = CURLINFO_TYPEMASK & (int)info;
  switch(type) {
  case CURLINFO_STRING:
    param_charp = va_arg(arg, const char **);
    if(param_charp)
      result = getinfo_char(data, info, param_charp);
    break;
  case CURLINFO_LONG:
    param_longp = va_arg(arg, long *);
    if(param_longp)
      result = getinfo_long(data, info, param_longp);
    break;
  case CURLINFO_DOUBLE:
    param_doublep = va_arg(arg, double *);
    if(param_doublep)
      result = getinfo_double(data, info, param_doublep);
    break;
  case CURLINFO_OFF_T:
    param_offt = va_arg(arg, curl_off_t *);
    if(param_offt)
      result = getinfo_offt(data, info, param_offt);
    break;
  case CURLINFO_SLIST:
    param_slistp = va_arg(arg, struct curl_slist **);
    if(param_slistp)
      result = getinfo_slist(data, info, param_slistp);
    break;
  case CURLINFO_SOCKET:
    param_socketp = va_arg(arg, curl_socket_t *);
    if(param_socketp)
      result = getinfo_socket(data, info, param_socketp);
    break;
  default:
    break;
  }

  va_end(arg);

  return result;
}