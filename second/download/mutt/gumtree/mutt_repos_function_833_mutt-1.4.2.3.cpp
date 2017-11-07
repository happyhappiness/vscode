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