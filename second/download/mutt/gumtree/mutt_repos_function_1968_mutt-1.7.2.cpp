static char *utf7_to_utf8 (const char *u7, size_t u7len, char **u8,
  size_t *u8len)
{
  char *buf, *p;
  int b, ch, k;

  p = buf = safe_malloc (u7len + u7len / 8 + 1);

  for (; u7len; u7++, u7len--)
  {
    if (*u7 == '&')
    {
      u7++, u7len--;

      if (u7len && *u7 == '-')
      {
	*p++ = '&';
	continue;
      }

      ch = 0;
      k = 10;
      for (; u7len; u7++, u7len--)
      {
	if ((*u7 & 0x80) || (b = Index_64[(int)*u7]) == -1)
	  break;
	if (k > 0)
	{
	  ch |= b << k;
	  k -= 6;
	}
	else
	{
	  ch |= b >> (-k);
	  if (ch < 0x80)
	  {
	    if (0x20 <= ch && ch < 0x7f)
	      /* Printable US-ASCII */
	      goto bail;
	    *p++ = ch;
	  }
	  else if (ch < 0x800)
	  {
	    *p++ = 0xc0 | (ch >> 6);
	    *p++ = 0x80 | (ch & 0x3f);
	  }
	  else
	  {
	    *p++ = 0xe0 | (ch >> 12);
	    *p++ = 0x80 | ((ch >> 6) & 0x3f);
	    *p++ = 0x80 | (ch & 0x3f);
	  }
	  ch = (b << (16 + k)) & 0xffff;
	  k += 10;
	}
      }
      if (ch || k < 6)
	/* Non-zero or too many extra bits */
	goto bail;
      if (!u7len || *u7 != '-')
	/* BASE64 not properly terminated */
	goto bail;
      if (u7len > 2 && u7[1] == '&' && u7[2] != '-')
	/* Adjacent BASE64 sections */
	goto bail;
    }
    else if (*u7 < 0x20 || *u7 >= 0x7f)
      /* Not printable US-ASCII */
      goto bail;
    else
      *p++ = *u7;
  }
  *p++ = '\0';
  if (u8len)
    *u8len = p - buf;

  safe_realloc (&buf, p - buf);
  if (u8)
    *u8 = buf;
  return buf;

 bail:
  FREE (&buf);
  return 0;
}