  fputc ('\n', fp);
}

/* arbitrary number of elements to grow the array by */
#define REF_INC 16

/* need to write the list in reverse because they are stored in reverse order
 * when parsed to speed up threading
 */
void mutt_write_references (LIST *r, FILE *f, int trim)
{
  LIST **ref = NULL;
  int refcnt = 0, refmax = 0;

  for ( ; (trim == 0 || refcnt < trim) && r ; r = r->next)
  {
    if (refcnt == refmax)
      safe_realloc (&ref, (refmax += REF_INC) * sizeof (LIST *));
    ref[refcnt++] = r;
  }

  while (refcnt-- > 0)
  {
    fputc (' ', f);
    fputs (ref[refcnt]->data, f);
    if (refcnt >= 1)
      fputc ('\n', f);
  }

  FREE (&ref);
}

static const char *find_word (const char *src)
{
  const char *p = src;

  while (p && *p && strchr (" \t\n", *p))
    p++;
  while (p && *p && !strchr (" \t\n", *p))
    p++;
  return p;
}

/* like wcwidth(), but gets const char* not wchar_t* */
static int my_width (const char *str, int col, int flags)
{
  wchar_t wc;
  int l, w = 0, nl = 0;
  const char *p = str;

  while (p && *p)
  {
    if (mbtowc (&wc, p, MB_CUR_MAX) >= 0)
    {
      l = wcwidth (wc);
      if (l < 0)
	l = 1;
      /* correctly calc tab stop, even for sending as the
       * line should look pretty on the receiving end */
      if (wc == L'\t' || (nl && wc == L' '))
      {
	nl = 0;
	l = 8 - (col % 8);
      }
      /* track newlines for display-case: if we have a space
       * after a newline, assume 8 spaces as for display we
       * always tab-fold */
      else if ((flags & CH_DISPLAY) && wc == '\n')
	nl = 1;
    }
    else
      l = 1;
    w += l;
    p++;
  }
  return w;
}

static int print_val (FILE *fp, const char *pfx, const char *value,
		      int flags, size_t col)
{
  while (value && *value)
  {
    if (fputc (*value, fp) == EOF)
      return -1;
    /* corner-case: break words longer than 998 chars by force,
     * mandated by RfC5322 */
    if (!(flags & CH_DISPLAY) && ++col >= 998)
    {
      if (fputs ("\n ", fp) < 0)
	return -1;
      col = 1;
    }
    if (*value == '\n')
    {
      if (*(value + 1) && pfx && *pfx && fputs (pfx, fp) == EOF)
	return -1;
      /* for display, turn folding spaces into folding tabs */
      if ((flags & CH_DISPLAY) && (*(value + 1) == ' ' || *(value + 1) == '\t'))
      {
	value++;
	while (*value && (*value == ' ' || *value == '\t'))
	  value++;
	if (fputc ('\t', fp) == EOF)
	  return -1;
	continue;
      }
    }
    value++;
  }
  return 0;
}

static int fold_one_header (FILE *fp, const char *tag, const char *value,
			      const char *pfx, int wraplen, int flags)
{
  const char *p = value, *next, *sp;
  char buf[HUGE_STRING] = "";
  int first = 1, enc, col = 0, w, l = 0, fold;

  dprint(4,(debugfile,"mwoh: pfx=[%s], tag=[%s], flags=%d value=[%s]\n",
	    pfx, tag, flags, value));

  if (tag && *tag && fprintf (fp, "%s%s: ", NONULL (pfx), tag) < 0)
    return -1;
  col = mutt_strlen (tag) + (tag && *tag ? 2 : 0) + mutt_strlen (pfx);

  while (p && *p)
  {
    fold = 0;

    /* find the next word and place it in `buf'. it may start with
     * whitespace we can fold before */
    next = find_word (p);
    l = MIN(sizeof (buf) - 1, next - p);
    memcpy (buf, p, l);
    buf[l] = 0;

    /* determine width: character cells for display, bytes for sending
     * (we get pure ascii only) */
    w = my_width (buf, col, flags);
    enc = mutt_strncmp (buf, "=?", 2) == 0;

    dprint(5,(debugfile,"mwoh: word=[%s], col=%d, w=%d, next=[0x0%x]\n",
	      buf, col, w, *next));

    /* insert a folding \n before the current word's lwsp except for
     * header name, first word on a line (word longer than wrap width)
     * and encoded words */
    if (!first && !enc && col && col + w >= wraplen)
    {
      col = mutt_strlen (pfx);
      fold = 1;
      if (fprintf (fp, "\n%s", NONULL(pfx)) <= 0)
	return -1;
    }

    /* print the actual word; for display, ignore leading ws for word
     * and fold with tab for readability */
    if ((flags & CH_DISPLAY) && fold)
    {
      char *p = buf;
      while (*p && (*p == ' ' || *p == '\t'))
      {
	p++;
	col--;
      }
      if (fputc ('\t', fp) == EOF)
	return -1;
      if (print_val (fp, pfx, p, flags, col) < 0)
	return -1;
      col += 8;
    }
    else if (print_val (fp, pfx, buf, flags, col) < 0)
      return -1;
    col += w;

    /* if the current word ends in \n, ignore all its trailing spaces
     * and reset column; this prevents us from putting only spaces (or
     * even none) on a line if the trailing spaces are located at our
     * current line width
     * XXX this covers ASCII space only, for display we probably
     * XXX want something like iswspace() here */
    sp = next;
    while (*sp && (*sp == ' ' || *sp == '\t'))
      sp++;
    if (*sp == '\n')
    {
      next = sp;
      col = 0;
    }

    p = next;
    first = 0;
  }

  /* if we have printed something but didn't \n-terminate it, do it
   * except the last word we printed ended in \n already */
  if (col && buf[l - 1] != '\n')
    if (putc ('\n', fp) == EOF)
      return -1;

  return 0;
}

static char *unfold_header (char *s)
{
  char *p = s, *q = s;

  while (p && *p)
  {
    /* remove CRLF prior to FWSP, turn \t into ' ' */
    if (*p == '\r' && *(p + 1) && *(p + 1) == '\n' && *(p + 2) &&
	(*(p + 2) == ' ' || *(p + 2) == '\t'))
    {
      *q++ = ' ';
      p += 3;
      continue;
    }
    /* remove LF prior to FWSP, turn \t into ' ' */
    else if (*p == '\n' && *(p + 1) && (*(p + 1) == ' ' || *(p + 1) == '\t'))
    {
      *q++ = ' ';
      p += 2;
      continue;
    }
    *q++ = *p++;
  }
  if (q)
    *q = 0;

  return s;
}

static int write_one_header (FILE *fp, int pfxw, int max, int wraplen,
			     const char *pfx, const char *start, const char *end,
			     int flags)
{
  char *tagbuf, *valbuf, *t;
  int is_from = ((end - start) > 5 &&
		 ascii_strncasecmp (start, "from ", 5) == 0);

  /* only pass through folding machinery if necessary for sending,
     never wrap From_ headers on sending */
  if (!(flags & CH_DISPLAY) && (pfxw + max <= wraplen || is_from))
  {
    valbuf = mutt_substrdup (start, end);
    dprint(4,(debugfile,"mwoh: buf[%s%s] short enough, "
	      "max width = %d <= %d\n",
	      NONULL(pfx), valbuf, max, wraplen));
    if (pfx && *pfx)
      if (fputs (pfx, fp) == EOF)
	return -1;
    if (!(t = strchr (valbuf, ':')))
    {
      dprint (1, (debugfile, "mwoh: warning: header not in "
		  "'key: value' format!\n"));
      return 0;
    }
    if (print_val (fp, pfx, valbuf, flags, mutt_strlen (pfx)) < 0)
    {
      FREE(&valbuf);
      return -1;
    }
    FREE(&valbuf);
  }
  else
  {
    t = strchr (start, ':');
    if (!t || t > end)
    {
      dprint (1, (debugfile, "mwoh: warning: header not in "
		  "'key: value' format!\n"));
      return 0;
    }
    if (is_from)
    {
      tagbuf = NULL;
      valbuf = mutt_substrdup (start, end);
    }
    else
    {
      tagbuf = mutt_substrdup (start, t);
      /* skip over the colon separating the header field name and value */
      t = skip_email_wsp(t + 1);
      valbuf = mutt_substrdup (t, end);
    }
    dprint(4,(debugfile,"mwoh: buf[%s%s] too long, "
	      "max width = %d > %d\n",
	      NONULL(pfx), valbuf, max, wraplen));
    if (fold_one_header (fp, tagbuf, valbuf, pfx, wraplen, flags) < 0)
      return -1;
    FREE (&tagbuf);
    FREE (&valbuf);
  }
  return 0;
}

/* split several headers into individual ones and call write_one_header
 * for each one */
int mutt_write_one_header (FILE *fp, const char *tag, const char *value,
			   const char *pfx, int wraplen, int flags)
{
  char *p = (char *)value, *last, *line;
  int max = 0, w, rc = -1;
  int pfxw = mutt_strwidth (pfx);
  char *v = safe_strdup (value);

  if (!(flags & CH_DISPLAY) || option (OPTWEED))
    v = unfold_header (v);

  /* when not displaying, use sane wrap value */
  if (!(flags & CH_DISPLAY))
  {
    if (WrapHeaders < 78 || WrapHeaders > 998)
      wraplen = 78;
    else
      wraplen = WrapHeaders;
  }
  else if (wraplen <= 0 || wraplen > COLS)
    wraplen = COLS;

  if (tag)
  {
    /* if header is short enough, simply print it */
    if (!(flags & CH_DISPLAY) && mutt_strwidth (tag) + 2 + pfxw +
	mutt_strwidth (v) <= wraplen)
    {
      dprint(4,(debugfile,"mwoh: buf[%s%s: %s] is short enough\n",
		NONULL(pfx), tag, v));
      if (fprintf (fp, "%s%s: %s\n", NONULL(pfx), tag, v) <= 0)
	goto out;
      rc = 0;
      goto out;
    }
    else
    {
      rc = fold_one_header (fp, tag, v, pfx, wraplen, flags);
      goto out;
    }
  }

  p = last = line = (char *)v;
  while (p && *p)
  {
    p = strchr (p, '\n');

    /* find maximum line width in current header */
    if (p)
      *p = 0;
    if ((w = my_width (line, 0, flags)) > max)
      max = w;
    if (p)
      *p = '\n';

    if (!p)
      break;

    line = ++p;
    if (*p != ' ' && *p != '\t')
    {
      if (write_one_header (fp, pfxw, max, wraplen, pfx, last, p, flags) < 0)
	goto out;
      last = p;
      max = 0;
    }
  }

  if (last && *last)
    if (write_one_header (fp, pfxw, max, wraplen, pfx, last, p, flags) < 0)
      goto out;

  rc = 0;

out:
  FREE (&v);
  return rc;
}


/* Note: all RFC2047 encoding should be done outside of this routine, except
 * for the "real name."  This will allow this routine to be used more than
 * once, if necessary.
 *
 * Likewise, all IDN processing should happen outside of this routine.
 *
 * mode == 1  => "lite" mode (used for edit_hdrs)
 * mode == 0  => normal mode.  write full header + MIME headers
 * mode == -1 => write just the envelope info (used for postponing messages)
 *
 * privacy != 0 => will omit any headers which may identify the user.
 *               Output generated is suitable for being sent through
 * 		 anonymous remailer chains.
 *
 */



int mutt_write_rfc822_header (FILE *fp, ENVELOPE *env, BODY *attach,
			      int mode, int privacy)
{
  char buffer[LONG_STRING];
  char *p, *q;
  LIST *tmp = env->userhdrs;
  int has_agent = 0; /* user defined user-agent header field exists */

  if (mode == 0 && !privacy)
    fputs (mutt_make_date (buffer, sizeof(buffer)), fp);

  /* OPTUSEFROM is not consulted here so that we can still write a From:
   * field if the user sets it with the `my_hdr' command
   */
  if (env->from && !privacy)
  {
    buffer[0] = 0;
    rfc822_write_address (buffer, sizeof (buffer), env->from, 0);
    fprintf (fp, "From: %s\n", buffer);
  }

  if (env->sender && !privacy)
  {
    buffer[0] = 0;
    rfc822_write_address (buffer, sizeof (buffer), env->sender, 0);
    fprintf (fp, "Sender: %s\n", buffer);
  }

  if (env->to)
  {
    fputs ("To: ", fp);
    mutt_write_address_list (env->to, fp, 4, 0);
  }
  else if (mode > 0)
    fputs ("To: \n", fp);

  if (env->cc)
  {
    fputs ("Cc: ", fp);
    mutt_write_address_list (env->cc, fp, 4, 0);
  }
  else if (mode > 0)
    fputs ("Cc: \n", fp);

  if (env->bcc)
  {
    if(mode != 0 || option(OPTWRITEBCC))
    {
      fputs ("Bcc: ", fp);
      mutt_write_address_list (env->bcc, fp, 5, 0);
    }
  }
  else if (mode > 0)
    fputs ("Bcc: \n", fp);

  if (env->subject)
    mutt_write_one_header (fp, "Subject", env->subject, NULL, 0, 0);
  else if (mode == 1)
    fputs ("Subject: \n", fp);

  /* save message id if the user has set it */
  if (env->message_id && !privacy)
    fprintf (fp, "Message-ID: %s\n", env->message_id);

  if (env->reply_to)
  {
    fputs ("Reply-To: ", fp);
    mutt_write_address_list (env->reply_to, fp, 10, 0);
  }
  else if (mode > 0)
    fputs ("Reply-To: \n", fp);

  if (env->mail_followup_to)
  {
    fputs ("Mail-Followup-To: ", fp);
    mutt_write_address_list (env->mail_followup_to, fp, 18, 0);
  }

  if (mode <= 0)
  {
    if (env->references)
    {
      fputs ("References:", fp);
      mutt_write_references (env->references, fp, 10);
      fputc('\n', fp);
    }

    /* Add the MIME headers */
    fputs ("MIME-Version: 1.0\n", fp);
    mutt_write_mime_header (attach, fp);
  }

  if (env->in_reply_to)
  {
    fputs ("In-Reply-To:", fp);
    mutt_write_references (env->in_reply_to, fp, 0);
    fputc ('\n', fp);
  }

  /* Add any user defined headers */
  for (; tmp; tmp = tmp->next)
  {
    if ((p = strchr (tmp->data, ':')))
    {
      q = p;

      *p = '\0';

      p = skip_email_wsp(p + 1);
      if (!*p)
      {
	*q = ':';
	continue;  /* don't emit empty fields. */
      }

      /* check to see if the user has overridden the user-agent field */
      if (!ascii_strncasecmp ("user-agent", tmp->data, 10))
      {
	has_agent = 1;
	if (privacy)
	{
	  *q = ':';
	  continue;
	}
      }

      mutt_write_one_header (fp, tmp->data, p, NULL, 0, 0);
      *q = ':';
    }
  }

  if (mode == 0 && !privacy && option (OPTXMAILER) && !has_agent)
  {
    /* Add a vanity header */
    fprintf (fp, "User-Agent: Mutt/%s (%s)\n", MUTT_VERSION, ReleaseDate);
  }

  return (ferror (fp) == 0 ? 0 : -1);
}

static void encode_headers (LIST *h)
{
  char *tmp;
  char *p;
  int i;

  for (; h; h = h->next)
  {
    if (!(p = strchr (h->data, ':')))
      continue;

    i = p - h->data;
    p = skip_email_wsp(p + 1);
    tmp = safe_strdup (p);

    if (!tmp)
      continue;

    rfc2047_encode_string (&tmp);
    safe_realloc (&h->data, mutt_strlen (h->data) + 2 + mutt_strlen (tmp) + 1);

    sprintf (h->data + i, ": %s", NONULL (tmp));  /* __SPRINTF_CHECKED__ */

    FREE (&tmp);
  }
}

const char *mutt_fqdn(short may_hide_host)
{
  char *p = NULL;

  if(Fqdn && Fqdn[0] != '@')
  {
    p = Fqdn;

    if(may_hide_host && option(OPTHIDDENHOST))
    {
      if((p = strchr(Fqdn, '.')))
	p++;

      /* sanity check: don't hide the host if
       * the fqdn is something like detebe.org.
       */

      if(!p || !strchr(p, '.'))
	p = Fqdn;
    }
  }

  return p;
}
