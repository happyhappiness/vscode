const char *
curl_share_strerror(CURLSHcode error)
{
#ifndef CURL_DISABLE_VERBOSE_STRINGS
  switch (error) {
  case CURLSHE_OK:
    return "no error";

  case CURLSHE_BAD_OPTION:
    return "unknown share option";

  case CURLSHE_IN_USE:
    return "share currently in use";

  case CURLSHE_INVALID:
    return "invalid share handle";

  case CURLSHE_NOMEM:
    return "out of memory";

  case CURLSHE_LAST:
    break;
  }

  return "CURLSH unknown";
#else
  if (error == CURLSHE_OK)
    return "no error";
  else
    return "error";
#endif
}