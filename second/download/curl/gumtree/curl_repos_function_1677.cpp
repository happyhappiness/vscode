static int encodeOID(char * buf, int n, const char * beg, const char * end)
{
  int i = 0;
  unsigned int x;
  unsigned int y;

  /* Convert an ASN.1 OID into its dotted string representation.
     Store the result in th `n'-byte buffer at `buf'.
     Return the converted string length, or -1 if an error occurs. */

  /* Process the first two numbers. */
  y = *(const unsigned char *) beg++;
  x = y / 40;
  y -= x * 40;
  i += encodeUint(buf + i, n - i, x);
  if(i < n)
    buf[i] = '.';
  i++;
  i += encodeUint(buf + i, n - i, y);

  /* Process the trailing numbers. */
  while(beg < end) {
    if(i < n)
      buf[i] = '.';
    i++;
    x = 0;
    do {
      if(x & 0xFF000000)
        return -1;
      y = *(const unsigned char *) beg++;
      x = (x << 7) | (y & 0x7F);
    } while(y & 0x80);
    i += encodeUint(buf + i, n - i, x);
  }
  if(i < n)
    buf[i] = '\0';
  return i;
}