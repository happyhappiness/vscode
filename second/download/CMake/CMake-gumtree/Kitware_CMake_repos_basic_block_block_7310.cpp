{
  char *buf;

  /* Convert an ASN.1 String into its UTF-8 string representation.
     Return the dynamically allocated string, or NULL if an error occurs. */

  if(utf8asn1str(&buf, type, beg, end) < 0)
    return (const char *) NULL;
  return buf;
}