static int
inet_pton4(const char *src, unsigned char *dst)
{
  static const char digits[] = "0123456789";
  int saw_digit, octets, ch;
  unsigned char tmp[INADDRSZ], *tp;

  saw_digit = 0;
  octets = 0;
  tp = tmp;
  *tp = 0;
  while ((ch = *src++) != '\0') {
    const char *pch;

    if ((pch = strchr(digits, ch)) != NULL) {
      u_int val = *tp * 10 + (u_int)(pch - digits);

      if (val > 255)
        return (0);
      *tp = val;
      if (! saw_digit) {
        if (++octets > 4)
          return (0);
        saw_digit = 1;
      }
    } else if (ch == '.' && saw_digit) {
      if (octets == 4)
        return (0);
      *++tp = 0;
      saw_digit = 0;
    } else
      return (0);
  }
  if (octets < 4)
    return (0);
  /* bcopy(tmp, dst, INADDRSZ); */
  memcpy(dst, tmp, INADDRSZ);
  return (1);
}