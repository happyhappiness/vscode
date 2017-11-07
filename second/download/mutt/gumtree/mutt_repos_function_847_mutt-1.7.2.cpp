static int address_header_decode (char **h)
{
  char *s = *h;
  int l, rp = 0;

  ADDRESS *a = NULL;
  ADDRESS *cur = NULL;

  switch (tolower ((unsigned char) *s))
  {
    case 'r': 
    {
      if (ascii_strncasecmp (s, "return-path:", 12) == 0)
      {
	l = 12;
	rp = 1;
	break;
      }
      else if (ascii_strncasecmp (s, "reply-to:", 9) == 0)
      {
	l = 9;
	break;
      }
      return 0;
    }
    case 'f': 
    {
      if (ascii_strncasecmp (s, "from:", 5)) 
	return 0; 
      l = 5;
      break;
    }
    case 'c':
    {
      if (ascii_strncasecmp (s, "cc:", 3))
	return 0;
      l = 3;
      break;
      
    }
    case 'b':
    {
      if (ascii_strncasecmp (s, "bcc:", 4))
	return 0;
      l = 4;
      break;
    }
    case 's':
    {
      if (ascii_strncasecmp (s, "sender:", 7))
	return 0;
      l = 7;
      break;
    }
    case 't':
    {
      if (ascii_strncasecmp (s, "to:", 3))
	return 0;
      l = 3;
      break;
    }
    case 'm':
    {
      if (ascii_strncasecmp (s, "mail-followup-to:", 17))
	return 0;
      l = 17;
      break;
    }
    default: return 0;    
  }

  if ((a = rfc822_parse_adrlist (a, s + l)) == NULL)
    return 0;
  
  mutt_addrlist_to_local (a);
  rfc2047_decode_adrlist (a);
  for (cur = a; cur; cur = cur->next)
    if (cur->personal)
      rfc822_dequote_comment (cur->personal);

  /* angle brackets for return path are mandated by RfC5322,
   * so leave Return-Path as-is */
  if (rp)
    *h = safe_strdup (s);
  else
  {
    *h = safe_calloc (1, l + 2);
    strfcpy (*h, s, l + 1);
    format_address_header (h, a);
  }

  rfc822_free_address (&a);

  FREE (&s);
  return 1;
}