int mutt_parse_rfc822_line (ENVELOPE *e, HEADER *hdr, char *line, char *p, short user_hdrs, short weed,
			    short do_2047, LIST **lastp)
{
  int matched = 0;
  LIST *last = NULL;
  
  if (lastp)
    last = *lastp;
  
  switch (ascii_tolower (line[0]))
  {
    case 'a':
    if (ascii_strcasecmp (line+1, "pparently-to") == 0)
    {
      e->to = rfc822_parse_adrlist (e->to, p);
      matched = 1;
    }
    else if (ascii_strcasecmp (line+1, "pparently-from") == 0)
    {
      e->from = rfc822_parse_adrlist (e->from, p);
      matched = 1;
    }
    break;
    
    case 'b':
    if (ascii_strcasecmp (line+1, "cc") == 0)
    {
      e->bcc = rfc822_parse_adrlist (e->bcc, p);
      matched = 1;
    }
    break;
    
    case 'c':
    if (ascii_strcasecmp (line+1, "c") == 0)
    {
      e->cc = rfc822_parse_adrlist (e->cc, p);
      matched = 1;
    }
    else if (ascii_strncasecmp (line + 1, "ontent-", 7) == 0)
    {
      if (ascii_strcasecmp (line+8, "type") == 0)
      {
	if (hdr)
	  mutt_parse_content_type (p, hdr->content);
	matched = 1;
      }
      else if (ascii_strcasecmp (line+8, "transfer-encoding") == 0)
      {
	if (hdr)
	  hdr->content->encoding = mutt_check_encoding (p);
	matched = 1;
      }
      else if (ascii_strcasecmp (line+8, "length") == 0)
      {
	if (hdr)
	{
	  if ((hdr->content->length = atol (p)) < 0)
	    hdr->content->length = -1;
	}
	matched = 1;
      }
      else if (ascii_strcasecmp (line+8, "description") == 0)
      {
	if (hdr)
	{
	  mutt_str_replace (&hdr->content->description, p);
	  rfc2047_decode (&hdr->content->description);
	}
	matched = 1;
      }
      else if (ascii_strcasecmp (line+8, "disposition") == 0)
      {
	if (hdr)
	  parse_content_disposition (p, hdr->content);
	matched = 1;
      }
    }
    break;
    
    case 'd':
    if (!ascii_strcasecmp ("ate", line + 1))
    {
      mutt_str_replace (&e->date, p);
      if (hdr)
	hdr->date_sent = mutt_parse_date (p, hdr);
      matched = 1;
    }
    break;
    
    case 'e':
    if (!ascii_strcasecmp ("xpires", line + 1) &&
	hdr && mutt_parse_date (p, NULL) < time (NULL))
      hdr->expired = 1;
    break;
    
    case 'f':
    if (!ascii_strcasecmp ("rom", line + 1))
    {
      e->from = rfc822_parse_adrlist (e->from, p);
      matched = 1;
    }
    break;
    
    case 'i':
    if (!ascii_strcasecmp (line+1, "n-reply-to"))
    {
      mutt_free_list (&e->in_reply_to);
      e->in_reply_to = mutt_parse_references (p, 1);
      matched = 1;
    }
    break;
    
    case 'l':
    if (!ascii_strcasecmp (line + 1, "ines"))
    {
      if (hdr)
      {
	/* 
	 * HACK - mutt has, for a very short time, produced negative
	 * Lines header values.  Ignore them. 
	 */
	if (mutt_atoi (p, &hdr->lines) < 0 || hdr->lines < 0)
	  hdr->lines = 0;
      }

      matched = 1;
    }
    else if (!ascii_strcasecmp (line + 1, "ist-Post"))
    {
      /* RFC 2369.  FIXME: We should ignore whitespace, but don't. */
      if (strncmp (p, "NO", 2))
      {
	char *beg, *end;
	for (beg = strchr (p, '<'); beg; beg = strchr (end, ','))
	{
	  ++beg;
	  if (!(end = strchr (beg, '>')))
	    break;
	  
	  /* Take the first mailto URL */
	  if (url_check_scheme (beg) == U_MAILTO)
	  {
	    FREE (&e->list_post);
	    e->list_post = mutt_substrdup (beg, end);
	    break;
	  }
	}
      }
      matched = 1;
    }
    break;
    
    case 'm':
    if (!ascii_strcasecmp (line + 1, "ime-version"))
    {
      if (hdr)
	hdr->mime = 1;
      matched = 1;
    }
    else if (!ascii_strcasecmp (line + 1, "essage-id"))
    {
      /* We add a new "Message-ID:" when building a message */
      FREE (&e->message_id);
      e->message_id = mutt_extract_message_id (p, NULL);
      matched = 1;
    }
    else if (!ascii_strncasecmp (line + 1, "ail-", 4))
    {
      if (!ascii_strcasecmp (line + 5, "reply-to"))
      {
	/* override the Reply-To: field */
	rfc822_free_address (&e->reply_to);
	e->reply_to = rfc822_parse_adrlist (e->reply_to, p);
	matched = 1;
      }
      else if (!ascii_strcasecmp (line + 5, "followup-to"))
      {
	e->mail_followup_to = rfc822_parse_adrlist (e->mail_followup_to, p);
	matched = 1;
      }
    }
    break;
    
    case 'r':
    if (!ascii_strcasecmp (line + 1, "eferences"))
    {
      mutt_free_list (&e->references);
      e->references = mutt_parse_references (p, 0);
      matched = 1;
    }
    else if (!ascii_strcasecmp (line + 1, "eply-to"))
    {
      e->reply_to = rfc822_parse_adrlist (e->reply_to, p);
      matched = 1;
    }
    else if (!ascii_strcasecmp (line + 1, "eturn-path"))
    {
      e->return_path = rfc822_parse_adrlist (e->return_path, p);
      matched = 1;
    }
    else if (!ascii_strcasecmp (line + 1, "eceived"))
    {
      if (hdr && !hdr->received)
      {
	char *d = strrchr (p, ';');
	
	if (d)
	  hdr->received = mutt_parse_date (d + 1, NULL);
      }
    }
    break;
    
    case 's':
    if (!ascii_strcasecmp (line + 1, "ubject"))
    {
      if (!e->subject)
	e->subject = safe_strdup (p);
      matched = 1;
    }
    else if (!ascii_strcasecmp (line + 1, "ender"))
    {
      e->sender = rfc822_parse_adrlist (e->sender, p);
      matched = 1;
    }
    else if (!ascii_strcasecmp (line + 1, "tatus"))
    {
      if (hdr)
      {
	while (*p)
	{
	  switch(*p)
	  {
	    case 'r':
	    hdr->replied = 1;
	    break;
	    case 'O':
	      hdr->old = 1;
	    break;
	    case 'R':
	    hdr->read = 1;
	    break;
	  }
	  p++;
	}
      }
      matched = 1;
    }
    else if ((!ascii_strcasecmp ("upersedes", line + 1) ||
	      !ascii_strcasecmp ("upercedes", line + 1)) && hdr)
    {
      FREE(&e->supersedes);
      e->supersedes = safe_strdup (p);
    }
    break;
    
    case 't':
    if (ascii_strcasecmp (line+1, "o") == 0)
    {
      e->to = rfc822_parse_adrlist (e->to, p);
      matched = 1;
    }
    break;
    
    case 'x':
    if (ascii_strcasecmp (line+1, "-status") == 0)
    {
      if (hdr)
      {
	while (*p)
	{
	  switch (*p)
	  {
	    case 'A':
	    hdr->replied = 1;
	    break;
	    case 'D':
	    hdr->deleted = 1;
	    break;
	    case 'F':
	    hdr->flagged = 1;
	    break;
	    default:
	    break;
	  }
	  p++;
	}
      }
      matched = 1;
    }
    else if (ascii_strcasecmp (line+1, "-label") == 0)
    {
      FREE(&e->x_label);
      e->x_label = safe_strdup(p);
      matched = 1;
    }
    
    default:
    break;
  }
  
  /* Keep track of the user-defined headers */
  if (!matched && user_hdrs)
  {
    /* restore the original line */
    line[strlen (line)] = ':';
    
    if (weed && option (OPTWEED) && mutt_matches_ignore (line, Ignore)
	&& !mutt_matches_ignore (line, UnIgnore))
      goto done;

    if (last)
    {
      last->next = mutt_new_list ();
      last = last->next;
    }
    else
      last = e->userhdrs = mutt_new_list ();
    last->data = safe_strdup (line);
    if (do_2047)
      rfc2047_decode (&last->data);
  }

  done:
  
  *lastp = last;
  return matched;
}