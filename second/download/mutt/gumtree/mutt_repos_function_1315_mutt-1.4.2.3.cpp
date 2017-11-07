static char *utf8_to_utf7 (const char *u8, size_t u8len, char **u7,
  size_t *u7len)
{
  char *buf, *p;
  int ch;
  int n, i, b = 0, k = 0;
  int base64 = 0;

  /*
   * In the worst case we convert 2 chars to 7 chars. For example:
   * "\x10&\x10&..." -> "&ABA-&-&ABA-&-...".
   */
  p = buf = safe_malloc ((u8len / 2) * 7 + 6);

  while (u8len)
  {
    unsigned char c = *u8;

    if (c < 0x80)
      ch = c, n = 0;
    else if (c < 0xc2)
      goto bail;
    else if (c < 0xe0)
      ch = c & 0x1f, n = 1;
    else if (c < 0xf0)
      ch = c & 0x0f, n = 2;
    else if (c < 0xf8)
      ch = c & 0x07, n = 3;
    else if (c < 0xfc)
      ch = c & 0x03, n = 4;
    else if (c < 0xfe)
      ch = c & 0x01, n = 5;
    else
      goto bail;

    u8++, u8len--;
    if (n > u8len)
      goto bail;
    for (i = 0; i < n; i++)
    {
      if ((u8[i] & 0xc0) != 0x80)
	goto bail;
      ch = (ch << 6) | (u8[i] & 0x3f);
    }
    if (n > 1 && !(ch >> (n * 5 + 1)))
      goto bail;
    u8 += n, u8len -= n;

    if (ch < 0x20 || ch >= 0x7f)
    {
      if (!base64)
      {
	*p++ = '&';
	base64 = 1;
	b = 0;
	k = 10;
      }
      if (ch & ~0xffff)
	ch = 0xfffe;
      *p++ = B64Chars[b | ch >> k];
      k -= 6;
      for (; k >= 0; k -= 6)
	*p++ = B64Chars[(ch >> k) & 0x3f];
      b = (ch << (-k)) & 0x3f;
      k += 16;
    }
    else
    {
      if (base64)
      {
	if (k > 10)
	  *p++ = B64Chars[b];
	*p++ = '-';
	base64 = 0;
      }
      *p++ = ch;
      if (ch == '&')
	*p++ = '-';
    }
  }

  if (u8len)
  {
    safe_free ((void **) &buf);
    return 0;
  }

  if (base64)
  {
    if (k > 10)
      *p++ = B64Chars[b];
    *p++ = '-';
  }

  *p++ = '\0';
  if (u7len)
    *u7len = p - buf;
  safe_realloc ((void **) &buf, p - buf);
  if (u7)  *u7 = buf;
  return buf;

 bail:
  safe_free ((void **) &buf);
  return 0;
}