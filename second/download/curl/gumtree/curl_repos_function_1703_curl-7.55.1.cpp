CURLcode Curl_resolver_init(void **resolver)
{
  int status = ares_init((ares_channel*)resolver);
  if(status != ARES_SUCCESS) {
    if(status == ARES_ENOMEM)
      return CURLE_OUT_OF_MEMORY;
    else
      return CURLE_FAILED_INIT;
  }
  return CURLE_OK;
  /* make sure that all other returns from this function should destroy the
     ares channel before returning error! */
}