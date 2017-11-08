static const char *UTime2str(const char *beg, const char *end)
{
  const char *tzp;
  size_t tzl;
  const char *sec;

  /* Convert an ASN.1 UTC time to a printable string.
     Return the dynamically allocated string, or NULL if an error occurs. */

  for(tzp = beg; tzp < end && *tzp >= '0' && *tzp <= '9'; tzp++)
    ;
  /* Get the seconds. */
  sec = beg + 10;
  switch(tzp - sec) {
  case 0:
    sec = "00";
  case 2:
    break;
  default:
    return (const char *) NULL;
  }

  /* Process timezone. */
  if(tzp >= end)
    return (const char *) NULL;
  if(*tzp == 'Z') {
    tzp = "GMT";
    end = tzp + 3;
  }
  else
    tzp++;

  tzl = end - tzp;
  return curl_maprintf("%u%.2s-%.2s-%.2s %.2s:%.2s:%.2s %.*s",
                       20 - (*beg >= '5'), beg, beg + 2, beg + 4,
                       beg + 6, beg + 8, sec,
                       tzl, tzp);
}