static const char *bit2str(const char *beg, const char *end)
{
  /* Convert an ASN.1 bit string to a printable string.
     Return the dynamically allocated string, or NULL if an error occurs. */

  if(++beg > end)
    return (const char *) NULL;
  return octet2str(beg, end);
}