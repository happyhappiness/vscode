CURLcode
curl_easy_getinfo_ccsid(CURL * curl, CURLINFO info, ...)

{
  va_list arg;
  void * paramp;
  CURLcode ret;
  unsigned int ccsid;
  char * * cpp;
  char * s;
  char * d;
  struct SessionHandle * data;

  /* WARNING: unlike curl_easy_get_info(), the strings returned by this
     procedure have to be free'ed. */

  data = (struct SessionHandle *) curl;
  va_start(arg, info);
  paramp = va_arg(arg, void *);
  ret = Curl_getinfo(data, info, paramp);

  if (ret != CURLE_OK || ((int) info & CURLINFO_TYPEMASK) != CURLINFO_STRING) {
    va_end(arg);
    return ret;
    }

  ccsid = va_arg(arg, unsigned int);
  va_end(arg);
  cpp = (char * *) paramp;
  s = *cpp;

  if (!s)
    return ret;

  d = dynconvert(ccsid, s, -1, ASCII_CCSID);
  *cpp = d;

  if (!d)
    return CURLE_OUT_OF_MEMORY;

  return ret;
}