static int encodeUint(char *buf, int n, unsigned int x)
{
  int i = 0;
  unsigned int y = x / 10;

  /* Decimal ASCII encode unsigned integer `x' in the `n'-byte buffer at `buf'.
     Return the total number of encoded digits, even if larger than `n'. */

  if(y) {
    i += encodeUint(buf, n, y);
    x -= y * 10;
  }
  if(i < n)
    buf[i] = (char) ('0' + x);
  i++;
  if(i < n)
    buf[i] = '\0';      /* Store a terminator if possible. */
  return i;
}