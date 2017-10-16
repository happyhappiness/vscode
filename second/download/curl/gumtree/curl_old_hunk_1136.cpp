  return curl_maprintf("%u%.2s-%.2s-%.2s %.2s:%.2s:%.2s %.*s",
                       20 - (*beg >= '5'), beg, beg + 2, beg + 4,
                       beg + 6, beg + 8, sec,
                       tzl, tzp);
}

const char * Curl_ASN1tostr(curl_asn1Element * elem, int type)
{
  /* Convert an ASN.1 element to a printable string.
     Return the dynamically allocated string, or NULL if an error occurs. */

  if(elem->constructed)
    return (const char *) NULL; /* No conversion of structured elements. */

  if(!type)
    type = elem->tag;   /* Type not forced: use element tag as type. */

  switch (type) {
  case CURL_ASN1_BOOLEAN:
    return bool2str(elem->beg, elem->end);
  case CURL_ASN1_INTEGER:
  case CURL_ASN1_ENUMERATED:
    return int2str(elem->beg, elem->end);
  case CURL_ASN1_BIT_STRING:
