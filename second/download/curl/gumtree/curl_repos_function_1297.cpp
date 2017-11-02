static bool
checkrtspprefix(struct SessionHandle *data,
                const char *s)
{

#ifdef CURL_DOES_CONVERSIONS
  /* convert from the network encoding using a scratch area */
  char *scratch = strdup(s);
  if(NULL == scratch) {
    failf (data, "Failed to allocate memory for conversion!");
    return FALSE; /* can't return CURLE_OUT_OF_MEMORY so return FALSE */
  }
  if(CURLE_OK != Curl_convert_from_network(data, scratch, strlen(s)+1)) {
    /* Curl_convert_from_network calls failf if unsuccessful */
    free(scratch);
    return FALSE; /* can't return CURLE_foobar so return FALSE */
  }
  s = scratch;
#else
  (void)data; /* unused */
#endif /* CURL_DOES_CONVERSIONS */
  if(checkprefix("RTSP/", s))
    return TRUE;
  else
    return FALSE;
}