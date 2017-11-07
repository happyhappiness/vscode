static int rfc2047_decode_word (char *d, const char *s, size_t len)
{
  const char *pp, *pp1;
  char *pd, *d0;
  const char *t, *t1;
  int enc = 0, count = 0;
  char *charset = NULL;
  int rv = -1;

  pd = d0 = safe_malloc (strlen (s));

  for (pp = s; (pp1 = strchr (pp, '?')); pp = pp1 + 1)
  {
    count++;

    /* hack for non-compliant MUAs that allow unquoted question marks in encoded-text */
    if (count == 4)
    {
      while (pp1 && *(pp1 + 1) != '=')
	pp1 = strchr(pp1 + 1, '?');
      if (!pp1)
	  goto error_out_0;
    }

    switch (count)
    {
      case 2:
	/* ignore language specification a la RFC 2231 */        
	t = pp1;
        if ((t1 = memchr (pp, '*', t - pp)))
	  t = t1;
	charset = mutt_substrdup (pp, t);
	break;
      case 3:
	if (toupper ((unsigned char) *pp) == 'Q')
	  enc = ENCQUOTEDPRINTABLE;
	else if (toupper ((unsigned char) *pp) == 'B')
	  enc = ENCBASE64;
	else
	  goto error_out_0;
	break;
      case 4:
	if (enc == ENCQUOTEDPRINTABLE)
	{
	  for (; pp < pp1; pp++)
	  {
	    if (*pp == '_')
	      *pd++ = ' ';
	    else if (*pp == '=' &&
		     (!(pp[1] & ~127) && hexval(pp[1]) != -1) &&
		     (!(pp[2] & ~127) && hexval(pp[2]) != -1))
	    {
	      *pd++ = (hexval(pp[1]) << 4) | hexval(pp[2]);
	      pp += 2;
	    }
	    else
	      *pd++ = *pp;
	  }
	  *pd = 0;
	}
	else if (enc == ENCBASE64)
	{
	  int c, b = 0, k = 0;

	  for (; pp < pp1; pp++)
	  {
	    if (*pp == '=')
	      break;
	    if ((*pp & ~127) || (c = base64val(*pp)) == -1)
	      continue;
	    if (k + 6 >= 8)
	    {
	      k -= 2;
	      *pd++ = b | (c >> k);
	      b = c << (8 - k);
	    }
	    else
	    {
	      b |= c << (k + 2);
	      k += 6;
	    }
	  }
	  *pd = 0;
	}
	break;
    }
  }
  
  if (charset)
    mutt_convert_string (&d0, charset, Charset, MUTT_ICONV_HOOK_FROM);
  mutt_filter_unprintable (&d0);
  strfcpy (d, d0, len);
  rv = 0;
error_out_0:
  FREE (&charset);
  FREE (&d0);
  return rv;
}