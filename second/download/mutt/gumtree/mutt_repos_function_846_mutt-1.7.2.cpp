static void format_address_header (char **h, ADDRESS *a)
{
  char buf[HUGE_STRING];
  char cbuf[STRING];
  char c2buf[STRING];
  char *p = NULL;
  int l, linelen, buflen, count, cbuflen, c2buflen, plen;

  linelen = mutt_strlen (*h);
  plen = linelen;
  buflen  = linelen + 3;

  safe_realloc (h, buflen);
  for (count = 0; a; a = a->next, count++)
  {
    ADDRESS *tmp = a->next;
    a->next = NULL;
    *buf = *cbuf = *c2buf = '\0';
    l = rfc822_write_address (buf, sizeof (buf), a, 0);
    a->next = tmp;
    
    if (count && linelen + l > 74) 
    {
      strcpy (cbuf, "\n\t");  	/* __STRCPY_CHECKED__ */
      linelen = l + 8;
    }
    else
    {
      if (a->mailbox)
      {
	strcpy (cbuf, " ");	/* __STRCPY_CHECKED__ */
	linelen++;
      }
      linelen += l;
    }
    if (!a->group && a->next && a->next->mailbox)
    {
      linelen++;
      buflen++;
      strcpy (c2buf, ",");	/* __STRCPY_CHECKED__ */
    }

    cbuflen = mutt_strlen (cbuf);
    c2buflen = mutt_strlen (c2buf);
    buflen += l + cbuflen + c2buflen;
    safe_realloc (h, buflen);
    p = *h;
    strcat (p + plen, cbuf);		/* __STRCAT_CHECKED__ */
    plen += cbuflen;
    strcat (p + plen, buf);		/* __STRCAT_CHECKED__ */
    plen += l;
    strcat (p + plen, c2buf);		/* __STRCAT_CHECKED__ */
    plen += c2buflen;
  }
  
  /* Space for this was allocated in the beginning of this function. */
  strcat (p + plen, "\n");		/* __STRCAT_CHECKED__ */
}