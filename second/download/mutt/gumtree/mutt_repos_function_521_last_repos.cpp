ENVELOPE *mutt_read_rfc822_header (FILE *f, HEADER *hdr, short user_hdrs,
				   short weed)
{
  ENVELOPE *e = mutt_new_envelope();
  LIST *last = NULL;
  char *line = safe_malloc (LONG_STRING);
  char *p;
  LOFF_T loc;
  size_t linelen = LONG_STRING;
  char buf[LONG_STRING+1];

  if (hdr)
  {
    if (hdr->content == NULL)
    {
      hdr->content = mutt_new_body ();

      /* set the defaults from RFC1521 */
      hdr->content->type        = TYPETEXT;
      hdr->content->subtype     = safe_strdup ("plain");
      hdr->content->encoding    = ENC7BIT;
      hdr->content->length      = -1;

      /* RFC 2183 says this is arbitrary */
      hdr->content->disposition = DISPINLINE;
    }
  }

  while ((loc = ftello (f)),
	  *(line = mutt_read_rfc822_line (f, line, &linelen)) != 0)
  {
    if ((p = strpbrk (line, ": \t")) == NULL || *p != ':')
    {
      char return_path[LONG_STRING];
      time_t t;

      /* some bogus MTAs will quote the original "From " line */
      if (mutt_strncmp (">From ", line, 6) == 0)
	continue; /* just ignore */
      else if (is_from (line, return_path, sizeof (return_path), &t))
      {
	/* MH sometimes has the From_ line in the middle of the header! */
	if (hdr && !hdr->received)
	  hdr->received = t - mutt_local_tz (t);
	continue;
      }

      fseeko (f, loc, 0);
      break; /* end of header */
    }

    *buf = '\0';

    if (mutt_match_spam_list(line, SpamList, buf, sizeof(buf)))
    {
      if (!mutt_match_rx_list(line, NoSpamList))
      {

	/* if spam tag already exists, figure out how to amend it */
	if (e->spam && *buf)
	{
	  /* If SpamSep defined, append with separator */
	  if (SpamSep)
	  {
	    mutt_buffer_addstr(e->spam, SpamSep);
	    mutt_buffer_addstr(e->spam, buf);
	  }

	  /* else overwrite */
	  else
	  {
	    e->spam->dptr = e->spam->data;
	    *e->spam->dptr = '\0';
	    mutt_buffer_addstr(e->spam, buf);
	  }
	}

	/* spam tag is new, and match expr is non-empty; copy */
	else if (!e->spam && *buf)
	{
	  e->spam = mutt_buffer_from (buf);
	}

	/* match expr is empty; plug in null string if no existing tag */
	else if (!e->spam)
	{
	  e->spam = mutt_buffer_from("");
	}

	if (e->spam && e->spam->data)
          dprint(5, (debugfile, "p822: spam = %s\n", e->spam->data));
      }
    }

    *p = 0;
    p = skip_email_wsp(p + 1);
    if (!*p)
      continue; /* skip empty header fields */

    mutt_parse_rfc822_line (e, hdr, line, p, user_hdrs, weed, 1, &last);
  }

  FREE (&line);

  if (hdr)
  {
    hdr->content->hdr_offset = hdr->offset;
    hdr->content->offset = ftello (f);

    /* do RFC2047 decoding */
    rfc2047_decode_adrlist (e->from);
    rfc2047_decode_adrlist (e->to);
    rfc2047_decode_adrlist (e->cc);
    rfc2047_decode_adrlist (e->bcc);
    rfc2047_decode_adrlist (e->reply_to);
    rfc2047_decode_adrlist (e->mail_followup_to);
    rfc2047_decode_adrlist (e->return_path);
    rfc2047_decode_adrlist (e->sender);
    rfc2047_decode (&e->x_label);

    if (e->subject)
    {
      regmatch_t pmatch[1];

      rfc2047_decode (&e->subject);

      if (regexec (ReplyRegexp.rx, e->subject, 1, pmatch, 0) == 0)
	e->real_subj = e->subject + pmatch[0].rm_eo;
      else
	e->real_subj = e->subject;
    }

    if (hdr->received < 0)
    {
      dprint(1,(debugfile,"read_rfc822_header(): resetting invalid received time to 0\n"));
      hdr->received = 0;
    }

    /* check for missing or invalid date */
    if (hdr->date_sent <= 0)
    {
      dprint(1,(debugfile,"read_rfc822_header(): no date found, using received time from msg separator\n"));
      hdr->date_sent = hdr->received;
    }
  }

  return (e);
}