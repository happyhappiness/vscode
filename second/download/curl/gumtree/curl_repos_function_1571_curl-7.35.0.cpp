static const char * GTime2str(const char * beg, const char * end)
{
  const char * tzp;
  const char * fracp;
  char sec1, sec2;
  size_t fracl;
  size_t tzl;
  const char * sep = "";

  /* Convert an ASN.1 Generalized time to a printable string.
     Return the dynamically allocated string, or NULL if an error occurs. */

  for(fracp = beg; fracp < end && *fracp >= '0' && *fracp <= '9'; fracp++)
    ;

  /* Get seconds digits. */
  sec1 = '0';
  switch (fracp - beg - 12) {
  case 0:
    sec2 = '0';
    break;
  case 2:
    sec1 = fracp[-2];
  case 1:
    sec2 = fracp[-1];
    break;
  default:
    return (const char *) NULL;
  }

  /* Scan for timezone, measure fractional seconds. */
  tzp = fracp;
  fracl = 0;
  if(fracp < end && (*fracp == '.' || *fracp == ',')) {
    fracp++;
    do
      tzp++;
    while(tzp < end && *tzp >= '0' && *tzp <= '9');
    /* Strip leading zeroes in fractional seconds. */
    for(fracl = tzp - fracp - 1; fracl && fracp[fracl - 1] == '0'; fracl--)
      ;
  }

  /* Process timezone. */
  if(tzp >= end)
    ;           /* Nothing to do. */
  else if(*tzp == 'Z') {
    tzp = " GMT";
    end = tzp + 4;
  }
  else {
    sep = " ";
    tzp++;
  }

  tzl = end - tzp;
  return curl_maprintf("%.4s-%.2s-%.2s %.2s:%.2s:%c%c%s%.*s%s%.*s",
                       beg, beg + 4, beg + 6,
                       beg + 8, beg + 10, sec1, sec2,
                       fracl? ".": "", fracl, fracp,
                       sep, tzl, tzp);
}