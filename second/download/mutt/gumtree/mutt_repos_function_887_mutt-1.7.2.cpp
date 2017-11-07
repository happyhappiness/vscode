static void my_wcstombs (char *dest, size_t dlen, const wchar_t *src, size_t slen)
{
  mbstate_t st;
  size_t k;

  /* First convert directly into the destination buffer */
  memset (&st, 0, sizeof (st));
  for (; slen && dlen >= MB_LEN_MAX; dest += k, dlen -= k, src++, slen--)
    if ((k = wcrtomb (dest, *src, &st)) == (size_t)(-1))
      break;

  /* If this works, we can stop now */
  if (dlen >= MB_LEN_MAX) {
    wcrtomb (dest, 0, &st);
    return;
  }

  /* Otherwise convert any remaining data into a local buffer */
  {
    char buf[3 * MB_LEN_MAX];
    char *p = buf;

    for (; slen && p - buf < dlen; p += k, src++, slen--)
      if ((k = wcrtomb (p, *src, &st)) == (size_t)(-1))
	break;
    p += wcrtomb (p, 0, &st);

    /* If it fits into the destination buffer, we can stop now */
    if (p - buf <= dlen) {
      memcpy (dest, buf, p - buf);
      return;
    }

    /* Otherwise we truncate the string in an ugly fashion */
    memcpy (dest, buf, dlen);
    dest[dlen - 1] = '\0'; /* assume original dlen > 0 */
  }
}