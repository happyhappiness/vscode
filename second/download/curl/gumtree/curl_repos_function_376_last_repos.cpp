char *
curl_pushheader_bynum_cssid(struct curl_pushheaders *h,
                            size_t num, unsigned int ccsid)

{
  char *d = (char *) NULL;
  char *s = curl_pushheader_bynum(h, num);

  if(s)
    d = dynconvert(ccsid, s, -1, ASCII_CCSID);

  return d;
}