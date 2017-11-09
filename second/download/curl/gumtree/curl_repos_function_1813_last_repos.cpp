static const char *bool2str(const char *beg, const char *end)
{
  /* Convert an ASN.1 Boolean value into its string representation.
     Return the dynamically allocated string, or NULL if source is not an
     ASN.1 Boolean value. */

  if(end - beg != 1)
    return (const char *) NULL;
  return strdup(*beg? "TRUE": "FALSE");
}