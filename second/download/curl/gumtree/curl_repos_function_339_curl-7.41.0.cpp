const char *
curl_easy_strerror_ccsid(CURLcode error, unsigned int ccsid)

{
  int i;
  const char * s;
  char * buf;

  s = curl_easy_strerror(error);

  if(!s)
    return s;

  i = MAX_CONV_EXPANSION * (strlen(s) + 1);

  if(!(buf = Curl_thread_buffer(LK_EASY_STRERROR, i)))
    return (const char *) NULL;

  if(convert(buf, i, ccsid, s, -1, ASCII_CCSID) < 0)
    return (const char *) NULL;

  return (const char *) buf;
}