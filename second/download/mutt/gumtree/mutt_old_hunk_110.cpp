
  rfc822_free_address (&env->mail_followup_to);

  /* back conversions */
  rfc2047_decode_adrlist (env->to);
  rfc2047_decode_adrlist (env->cc);
  rfc2047_decode_adrlist (env->from);
  rfc2047_decode_adrlist (env->reply_to);
  rfc2047_decode (&env->subject);
}

static void _mutt_bounce_message (FILE *fp, HEADER *h, ADDRESS *to, const char *resent_from,
				  ADDRESS *env_from)
{
  int i;
  FILE *f;
  char date[SHORT_STRING], tempfile[_POSIX_PATH_MAX];
  MESSAGE *msg = NULL;

  if (!h)
  {
    for (i=0; i<Context->msgcount; i++)
      if (Context->hdrs[i]->tagged)
	_mutt_bounce_message (fp, Context->hdrs[i], to, resent_from, env_from);
    return;
  }

  if (!fp && (msg = mx_open_message (Context, h->msgno)) == NULL)
    return;

  if (!fp) fp = msg->fp;

  mutt_mktemp (tempfile);
  if ((f = safe_fopen (tempfile, "w")) != NULL)
  {
    int ch_flags = CH_XMIT | CH_NONEWLINE;
    
    if (!option (OPTBOUNCEDELIVERED))
      ch_flags |= CH_WEED_DELIVERED;
    
    fseek (fp, h->offset, 0);
    mutt_copy_header (fp, h, f, ch_flags, NULL);
    fprintf (f, "Resent-From: %s", resent_from);
    fprintf (f, "\nResent-%s", mutt_make_date (date, sizeof(date)));
    fputs ("Resent-To: ", f);
    mutt_write_address_list (to, f, 11);
    fputc ('\n', f);
    mutt_copy_bytes (fp, f, h->content->length);
    fclose (f);

    mutt_invoke_sendmail (env_from, to, NULL, NULL, tempfile,
			  h->content->encoding == ENC8BIT);
  }

  if (msg)
    mx_close_message (&msg);
}

void mutt_bounce_message (FILE *fp, HEADER *h, ADDRESS *to)
{
  ADDRESS *from;
  const char *fqdn = mutt_fqdn (1);
  char resent_from[STRING];

  resent_from[0] = '\0';
  from = mutt_default_from ();

  if (fqdn)
    rfc822_qualify (from, fqdn);

  rfc2047_encode_adrlist (from, "Resent-From");
  
  rfc822_write_address (resent_from, sizeof (resent_from), from);

  _mutt_bounce_message (fp, h, to, resent_from, from);

  rfc822_free_address (&from);
}


/* given a list of addresses, return a list of unique addresses */
ADDRESS *mutt_remove_duplicates (ADDRESS *addr)
{
  ADDRESS *top = NULL;
  ADDRESS *tmp;
  
  if ((top = addr) == NULL)
    return (NULL);
  addr = addr->next;
  top->next = NULL;
  while (addr)
  {
    tmp = top;
    do {
      if (addr->mailbox && tmp->mailbox &&
	  !ascii_strcasecmp (addr->mailbox, tmp->mailbox))
      {
	/* duplicate address, just ignore it */
	tmp = addr;
	addr = addr->next;
	tmp->next = NULL;
	rfc822_free_address (&tmp);
      }
      else if (!tmp->next)
      {
	/* unique address.  add it to the list */
	tmp->next = addr;
	addr = addr->next;
	tmp = tmp->next;
	tmp->next = NULL;
	tmp = NULL; /* so we exit the loop */
      }
      else
	tmp = tmp->next;
    } while (tmp);
  }

  return (top);
}

static void set_noconv_flags (BODY *b, short flag)
