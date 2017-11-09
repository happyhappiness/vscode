const char *
curl_multi_strerror_ccsid(CURLMcode error, unsigned int ccsid)

{
  int i;
  const char * s;
  char * buf;

  s = curl_multi_strerror(error);

  if(!s)
    return s;

  i = MAX_CONV_EXPANSION * (strlen(s) + 1);

  if(!(buf = Curl_thread_buffer(LK_MULTI_STRERROR, i)))
    return (const char *) NULL;

  if(convert(buf, i, ccsid, s, -1, ASCII_CCSID) < 0)
    return (const char *) NULL;

  return (const char *) buf;
}