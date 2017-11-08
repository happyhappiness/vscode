time_t
curl_getdate_ccsid(const char * p, const time_t * unused, unsigned int ccsid)

{
  char * s;
  time_t t;

  if(!p)
    return curl_getdate(p, unused);

  s = dynconvert(ASCII_CCSID, p, -1, ccsid);

  if(!s)
    return (time_t) -1;

  t = curl_getdate(s, unused);
  free(s);
  return t;
}