int Curl_resolver_duphandle(void **to, void *from)
{
  /* Clone the ares channel for the new handle */
  if(ARES_SUCCESS != ares_dup((ares_channel*)to, (ares_channel)from))
    return CURLE_FAILED_INIT;
  return CURLE_OK;
}