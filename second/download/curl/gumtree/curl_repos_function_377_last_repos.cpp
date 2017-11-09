char *
curl_pushheader_byname_ccsid(struct curl_pushheaders *h, const char *header,
                             unsigned int ccsidin, unsigned int ccsidout)

{
  char *d = (char *) NULL;
  char *s;

  if(header) {
    header = dynconvert(ASCII_CCSID, header, -1, ccsidin);

    if(header) {
      s = curl_pushheader_byname(h, header);
      free((char *) header);

      if(s)
        d = dynconvert(ccsidout, s, -1, ASCII_CCSID);
    }
  }

  return d;
}