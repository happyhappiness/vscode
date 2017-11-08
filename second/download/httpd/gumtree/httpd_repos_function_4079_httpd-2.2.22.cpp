static int
valid_utf8(const uschar *string, int length)
{
register const uschar *p;

if (length < 0)
  {
  for (p = string; *p != 0; p++);
  length = p - string;
  }

for (p = string; length-- > 0; p++)
  {
  register int ab;
  register int c = *p;
  if (c < 128) continue;
  if ((c & 0xc0) != 0xc0) return p - string;
  ab = utf8_table4[c & 0x3f];  /* Number of additional bytes */
  if (length < ab) return p - string;
  length -= ab;

  /* Check top bits in the second byte */
  if ((*(++p) & 0xc0) != 0x80) return p - string;

  /* Check for overlong sequences for each different length */
  switch (ab)
    {
    /* Check for xx00 000x */
    case 1:
    if ((c & 0x3e) == 0) return p - string;
    continue;   /* We know there aren't any more bytes to check */

    /* Check for 1110 0000, xx0x xxxx */
    case 2:
    if (c == 0xe0 && (*p & 0x20) == 0) return p - string;
    break;

    /* Check for 1111 0000, xx00 xxxx */
    case 3:
    if (c == 0xf0 && (*p & 0x30) == 0) return p - string;
    break;

    /* Check for 1111 1000, xx00 0xxx */
    case 4:
    if (c == 0xf8 && (*p & 0x38) == 0) return p - string;
    break;

    /* Check for leading 0xfe or 0xff, and then for 1111 1100, xx00 00xx */
    case 5:
    if (c == 0xfe || c == 0xff ||
       (c == 0xfc && (*p & 0x3c) == 0)) return p - string;
    break;
    }

  /* Check for valid bytes after the 2nd, if any; all must start 10 */
  while (--ab > 0)
    {
    if ((*(++p) & 0xc0) != 0x80) return p - string;
    }
  }

return -1;
}