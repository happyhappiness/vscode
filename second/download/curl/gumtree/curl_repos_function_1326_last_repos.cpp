const char *
curl_share_strerror(CURLSHcode error)
{
#ifndef CURL_DISABLE_VERBOSE_STRINGS
  switch(error) {
  case CURLSHE_OK:
    return "No error";

  case CURLSHE_BAD_OPTION:
    return "Unknown share option";

  case CURLSHE_IN_USE:
    return "Share currently in use";

  case CURLSHE_INVALID:
    return "Invalid share handle";

  case CURLSHE_NOMEM:
    return "Out of memory";

  case CURLSHE_NOT_BUILT_IN:
    return "Feature not enabled in this library";

  case CURLSHE_LAST:
    break;
  }

  return "CURLSHcode unknown";
#else
  if(error == CURLSHE_OK)
    return "No error";
  else
    return "Error";
#endif
}