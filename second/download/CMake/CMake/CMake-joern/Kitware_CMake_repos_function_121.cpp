static const char *int2str(const char *beg, const char *end)
{
  long val = 0;
  size_t n = end - beg;

  /* Convert an ASN.1 integer value into its string representation.
     Return the dynamically allocated string, or NULL if source is not an
     ASN.1 integer value. */

  if(!n)
    return (const char *) NULL;

  if(n > 4)
    return octet2str(beg, end);

  /* Represent integers <= 32-bit as a single value. */
  if(*beg & 0x80)
    val = ~val;

  do
    val = (val << 8) | *(const unsigned char *) beg++;
  while(beg < end);
  return curl_maprintf("%s%lx", (val < 0 || val >= 10)? "0x": "", val);
}