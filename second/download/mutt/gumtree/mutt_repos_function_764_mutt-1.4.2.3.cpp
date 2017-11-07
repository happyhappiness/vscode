static int rfc2047_decode_word (char *d, const char *s, size_t len)
{
  const char *pp = s, *pp1;
  char *pd, *d0;
  const char *t, *t1;
  int enc = 0, count = 0, c1, c2, c3, c4;
  char *charset = NULL;

  pd = d0 = safe_malloc (strlen (s));

  for (pp = s; (pp1 = strchr (pp, '?')); pp = pp1 + 1)
  {
    count++;
    switch (count)
    {
      case 2:
	/* ignore language specification a la RFC 2231 */        
	t = pp1;
        if ((t1 = memchr (pp, '*', t - pp)))
	  t = t1;
	charset = safe_malloc (t - pp + 1);
	memcpy (charset, pp, t - pp);
	charset[t-pp] = '\0';
	break;
      case 3:
	if (toupper (*pp) == 'Q')
	  enc = ENCQUOTEDPRINTABLE;
	else if (toupper (*pp) == 'B')
	  enc = ENCBASE64;
	else
	{
	  safe_free ((void **) &charset);
	  safe_free ((void **) &d0);
	  return (-1);
	}
	break;
      case 4:
	if (enc == ENCQUOTEDPRINTABLE)
	{
	  while (pp < pp1 && len > 0)
	  {
	    if (*pp == '_')
	    {
	      *pd++ = ' ';
	      len--;
	    }
	    else if (*pp == '=')
	    {
	      if (pp[1] == 0 || pp[2] == 0)
		break;	/* something wrong */
	      *pd++ = (hexval(pp[1]) << 4) | hexval(pp[2]);
	      len--;
	      pp += 2;
	    }
	    else
	    {
	      *pd++ = *pp;
	      len--;
	    }
	    pp++;
	  }
	  *pd = 0;
	}
	else if (enc == ENCBASE64)
	{
	  while (pp < pp1 && len > 0)
	  {
	    if (pp[0] == '=' || pp[1] == 0 || pp[1] == '=')
	      break;  /* something wrong */
	    c1 = base64val(pp[0]);
	    c2 = base64val(pp[1]);
	    *pd++ = (c1 << 2) | ((c2 >> 4) & 0x3);
	    if (--len == 0) break;
	    
	    if (pp[2] == 0 || pp[2] == '=') break;

	    c3 = base64val(pp[2]);
	    *pd++ = ((c2 & 0xf) << 4) | ((c3 >> 2) & 0xf);
	    if (--len == 0)
	      break;

	    if (pp[3] == 0 || pp[3] == '=')
	      break;

	    c4 = base64val(pp[3]);
	    *pd++ = ((c3 & 0x3) << 6) | c4;
	    if (--len == 0)
	      break;

	    pp += 4;
	  }
	  *pd = 0;
	}
	break;
    }
  }
  
  if (charset)
    mutt_convert_string (&d0, charset, Charset, M_ICONV_HOOK_FROM);
  strfcpy (d, d0, len);
  safe_free ((void **) &charset);
  safe_free ((void **) &d0);
  return (0);
}