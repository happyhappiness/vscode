  fputc ('\n', fp);
}

/* arbitrary number of elements to grow the array by */
#define REF_INC 16

#define TrimRef 10

/* need to write the list in reverse because they are stored in reverse order
 * when parsed to speed up threading
 */
static void write_references (LIST *r, FILE *f)
{
  LIST **ref = NULL;
  int refcnt = 0, refmax = 0;

  for ( ; (TrimRef == 0 || refcnt < TrimRef) && r ; r = r->next)
  {
    if (refcnt == refmax)
      safe_realloc ((void **) &ref, (refmax += REF_INC) * sizeof (LIST *));
    ref[refcnt++] = r;
  }

  while (refcnt-- > 0)
  {
    fputc (' ', f);
    fputs (ref[refcnt]->data, f);
  }

  safe_free ((void **) &ref);
}

/* Note: all RFC2047 encoding should be done outside of this routine, except
 * for the "real name."  This will allow this routine to be used more than
 * once, if necessary.
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
  char *p;
  LIST *tmp = env->userhdrs;
  
  if (mode == 0 && !privacy)
    fputs (mutt_make_date (buffer, sizeof(buffer)), fp);

  /* OPTUSEFROM is not consulted here so that we can still write a From:
   * field if the user sets it with the `my_hdr' command
   */
  if (env->from && !privacy)
  {
    buffer[0] = 0;
    rfc822_write_address (buffer, sizeof (buffer), env->from);
    fprintf (fp, "From: %s\n", buffer);
  }

  if (env->to)
  {
    fputs ("To: ", fp);
    mutt_write_address_list (env->to, fp, 4);
  }
  else if (mode > 0)
    fputs ("To: \n", fp);

  if (env->cc)
  {
    fputs ("Cc: ", fp);
    mutt_write_address_list (env->cc, fp, 4);
  }
  else if (mode > 0)
    fputs ("Cc: \n", fp);

  if (env->bcc)
  {
    if(mode != 0 || option(OPTWRITEBCC))
    {
      fputs ("Bcc: ", fp);
      mutt_write_address_list (env->bcc, fp, 5);
    }
  }
  else if (mode > 0)
    fputs ("Bcc: \n", fp);

  if (env->subject)
    fprintf (fp, "Subject: %s\n", env->subject);
  else if (mode == 1)
    fputs ("Subject: \n", fp);

  /* save message id if the user has set it */
  if (env->message_id && !privacy)
    fprintf (fp, "Message-ID: %s\n", env->message_id);

  if (env->reply_to)
  {
    fputs ("Reply-To: ", fp);
    mutt_write_address_list (env->reply_to, fp, 10);
  }
  else if (mode > 0)
    fputs ("Reply-To: \n", fp);

  if (env->mail_followup_to)
  {
    fputs ("Mail-Followup-To: ", fp);
    mutt_write_address_list (env->mail_followup_to, fp, 18);
  }

  if (mode <= 0)
  {
    if (env->references)
    {
      fputs ("References:", fp);
      write_references (env->references, fp);
      fputc('\n', fp);
    }

    /* Add the MIME headers */
    fputs ("Mime-Version: 1.0\n", fp);
    mutt_write_mime_header (attach, fp);
  }

  if (env->in_reply_to)
  {
    fputs ("In-Reply-To:", fp);
    write_references (env->in_reply_to, fp);
    fputc ('\n', fp);
  }
  
  if (mode == 0 && !privacy && option (OPTXMAILER))
  {
    /* Add a vanity header */
    fprintf (fp, "User-Agent: Mutt/%s\n", MUTT_VERSION);
  }

  /* Add any user defined headers */
  for (; tmp; tmp = tmp->next)
  {
    if ((p = strchr (tmp->data, ':')))
    {
      p++; SKIPWS (p);
      if (!*p) 	continue;  /* don't emit empty fields. */

      fputs (tmp->data, fp);
      fputc ('\n', fp);
    }
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
    ++p; SKIPWS (p);
    tmp = safe_strdup (p);

    if (!tmp)
      continue;
    
    rfc2047_encode_string (&tmp);
    safe_realloc ((void **) &h->data, 
		  mutt_strlen (h->data) + 2 + mutt_strlen (tmp) + 1);

    sprintf (h->data + i, ": %s", NONULL (tmp));  /* __SPRINTF_CHECKED__ */
    
    safe_free ((void **) &tmp);
  }
}

const char *mutt_fqdn(short may_hide_host)
{
  char *p = NULL, *q;
  
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
      
      if(!p || !(q = strchr(p, '.')))
	p = Fqdn;
    }
  }

  return p;
}
