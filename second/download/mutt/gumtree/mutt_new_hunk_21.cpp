
  for (part = b->parts ; part ; part = part->next)
  {
    if (part->deleted || part->parts)
    {
      /* Copy till start of this part */
      if (mutt_copy_bytes (fpin, fpout, part->hdr_offset - ftello (fpin)))
	return -1;

      if (part->deleted)
      {
	fprintf (fpout,
		 "Content-Type: message/external-body; access-type=x-mutt-deleted;\n"
		 "\texpiration=%s; length=" OFF_T_FMT "\n"
		 "\n", date + 5, part->length);
	if (ferror (fpout))
	  return -1;

	/* Copy the original mime headers */
	if (mutt_copy_bytes (fpin, fpout, part->offset - ftello (fpin)))
	  return -1;

	/* Skip the deleted body */
	fseeko (fpin, part->offset + part->length, SEEK_SET);
      }
      else
      {
	if (copy_delete_attach (part, fpin, fpout, date))
	  return -1;
      }
    }
  }

  /* Copy the last parts */
  if (mutt_copy_bytes (fpin, fpout, b->offset + b->length - ftello (fpin)))
    return -1;

  return 0;
}

/* 
 * This function is the equivalent of mutt_write_address_list(),
 * but writes to a buffer instead of writing to a stream.
 * mutt_write_address_list could be re-used if we wouldn't store
 * all the decoded headers in a huge array, first. 
 *
 * XXX - fix that. 
 */

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
