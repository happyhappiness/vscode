static int _mutt_bounce_message (FILE *fp, HEADER *h, ADDRESS *to, const char *resent_from,
				  ADDRESS *env_from)
{
  int i, ret = 0;
  FILE *f;
  char date[SHORT_STRING], tempfile[_POSIX_PATH_MAX];
  MESSAGE *msg = NULL;

  if (!h)
  {
	  /* Try to bounce each message out, aborting if we get any failures. */
    for (i=0; i<Context->msgcount; i++)
      if (Context->hdrs[i]->tagged)
        ret |= _mutt_bounce_message (fp, Context->hdrs[i], to, resent_from, env_from);
    return ret;
  }

  /* If we failed to open a message, return with error */
  if (!fp && (msg = mx_open_message (Context, h->msgno)) == NULL)
    return -1;

  if (!fp) fp = msg->fp;

  mutt_mktemp (tempfile, sizeof (tempfile));
  if ((f = safe_fopen (tempfile, "w")) != NULL)
  {
    int ch_flags = CH_XMIT | CH_NONEWLINE | CH_NOQFROM;
    char* msgid_str;

    if (!option (OPTBOUNCEDELIVERED))
      ch_flags |= CH_WEED_DELIVERED;

    fseeko (fp, h->offset, 0);
    fprintf (f, "Resent-From: %s", resent_from);
    fprintf (f, "\nResent-%s", mutt_make_date (date, sizeof(date)));
    msgid_str = mutt_gen_msgid();
    fprintf (f, "Resent-Message-ID: %s\n", msgid_str);
    fputs ("Resent-To: ", f);
    mutt_write_address_list (to, f, 11, 0);
    mutt_copy_header (fp, h, f, ch_flags, NULL);
    fputc ('\n', f);
    mutt_copy_bytes (fp, f, h->content->length);
    safe_fclose (&f);
    FREE (&msgid_str);

#if USE_SMTP
    if (SmtpUrl)
      ret = mutt_smtp_send (env_from, to, NULL, NULL, tempfile,
                            h->content->encoding == ENC8BIT);
    else
#endif /* USE_SMTP */
    ret = mutt_invoke_sendmail (env_from, to, NULL, NULL, tempfile,
			  	h->content->encoding == ENC8BIT);
  }

  if (msg)
    mx_close_message (&msg);

  return ret;
}