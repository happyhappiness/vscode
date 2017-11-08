char *
curl_easy_escape_ccsid(CURL * handle, const char * string, int length,
                       unsigned int sccsid, unsigned int dccsid)

{
  char * s;
  char * d;

  if(!string) {
    errno = EINVAL;
    return (char *) NULL;
    }

  s = dynconvert(ASCII_CCSID, string, length? length: -1, sccsid);

  if(!s)
    return (char *) NULL;

  d = curl_easy_escape(handle, s, 0);
  free(s);

  if(!d)
    return (char *) NULL;

  s = dynconvert(dccsid, d, -1, ASCII_CCSID);
  free(d);
  return s;
}