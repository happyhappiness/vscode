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