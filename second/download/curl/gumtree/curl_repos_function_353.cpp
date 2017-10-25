const char *
curl_multi_strerror(CURLMcode error)
{
#ifndef CURL_DISABLE_VERBOSE_STRINGS
  switch (error) {
  case CURLM_CALL_MULTI_PERFORM:
    return "please call curl_multi_perform() soon";

  case CURLM_OK:
    return "no error";

  case CURLM_BAD_HANDLE:
    return "invalid multi handle";

  case CURLM_BAD_EASY_HANDLE:
    return "invalid easy handle";

  case CURLM_OUT_OF_MEMORY:
    return "out of memory";

  case CURLM_INTERNAL_ERROR:
    return "internal error";

  case CURLM_LAST:
    break;
  }

  return "unknown error";
#else
  if (error == CURLM_OK)
    return "no error";
  else
    return "error";
#endif
}