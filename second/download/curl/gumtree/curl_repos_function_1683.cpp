const char * Curl_DNtostr(curl_asn1Element * dn)
{
  char * buf = (char *) NULL;
  ssize_t n = encodeDN(buf, 0, dn);

  /* Convert an ASN.1 distinguished name into a printable string.
     Return the dynamically allocated string, or NULL if an error occurs. */

  if(n >= 0) {
    buf = malloc(n + 1);
    if(buf) {
      encodeDN(buf, n + 1, dn);
      buf[n] = '\0';
    }
  }
  return (const char *) buf;
}