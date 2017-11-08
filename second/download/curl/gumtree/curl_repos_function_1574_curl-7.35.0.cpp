static ssize_t encodeDN(char * buf, size_t n, curl_asn1Element * dn)
{
  curl_asn1Element rdn;
  curl_asn1Element atv;
  curl_asn1Element oid;
  curl_asn1Element value;
  size_t l = 0;
  const char * p1;
  const char * p2;
  const char * p3;
  const char * str;

  /* ASCII encode distinguished name at `dn' into the `n'-byte buffer at `buf'.
     Return the total string length, even if larger than `n'. */

  for(p1 = dn->beg; p1 < dn->end;) {
    p1 = Curl_getASN1Element(&rdn, p1, dn->end);
    for(p2 = rdn.beg; p2 < rdn.end;) {
      p2 = Curl_getASN1Element(&atv, p2, rdn.end);
      p3 = Curl_getASN1Element(&oid, atv.beg, atv.end);
      Curl_getASN1Element(&value, p3, atv.end);
      str = Curl_ASN1tostr(&oid, 0);
      if(!str)
        return -1;

      /* Encode delimiter.
         If attribute has a short uppercase name, delimiter is ", ". */
      if(l) {
        for(p3 = str; isupper(*p3); p3++)
          ;
        for(p3 = (*p3 || p3 - str > 2)? "/": ", "; *p3; p3++) {
          if(l < n)
            buf[l] = *p3;
          l++;
        }
      }

      /* Encode attribute name. */
      for(p3 = str; *p3; p3++) {
        if(l < n)
          buf[l] = *p3;
        l++;
      }
      free((char *) str);

      /* Generate equal sign. */
      if(l < n)
        buf[l] = '=';
      l++;

      /* Generate value. */
      str = Curl_ASN1tostr(&value, 0);
      if(!str)
        return -1;
      for(p3 = str; *p3; p3++) {
        if(l < n)
          buf[l] = *p3;
        l++;
      }
      free((char *) str);
    }
  }

  return l;
}