static bool
checkrtspprefix(struct Curl_easy *data,
                const char *s)
{
  bool result = FALSE;

#ifdef CURL_DOES_CONVERSIONS
  /* convert from the network encoding using a scratch area */
  char *scratch = strdup(s);
  if(NULL == scratch) {
    failf(data, "Failed to allocate memory for conversion!");
    return FALSE; /* can't return CURLE_OUT_OF_MEMORY so return FALSE */
  }
  if(CURLE_OK != Curl_convert_from_network(data, scratch, strlen(s) + 1)) {
    /* Curl_convert_from_network calls failf if unsuccessful */
    result = FALSE; /* can't return CURLE_foobar so return FALSE */
  }
  else
    result = checkprefix("RTSP/", scratch)? TRUE: FALSE;
  free(scratch);
#else
  (void)data; /* unused */
  result = checkprefix("RTSP/", s)? TRUE: FALSE;
#endif /* CURL_DOES_CONVERSIONS */

  return result;
}