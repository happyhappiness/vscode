static const char * OID2str(const char * beg, const char * end, bool symbolic)
{
  char * buf = (char *) NULL;
  const curl_OID * op;
  int n;

  /* Convert an ASN.1 OID into its dotted or symbolic string representation.
     Return the dynamically allocated string, or NULL if an error occurs. */

  if(beg < end) {
    n = encodeOID((char *) NULL, -1, beg, end);
    if(n >= 0) {
      buf = malloc(n + 1);
      if(buf) {
        encodeOID(buf, n, beg, end);
        buf[n] = '\0';

        if(symbolic) {
          op = searchOID(buf);
          if(op) {
            free(buf);
            buf = strdup(op->textoid);
          }
        }
      }
    }
  }
  return buf;
}