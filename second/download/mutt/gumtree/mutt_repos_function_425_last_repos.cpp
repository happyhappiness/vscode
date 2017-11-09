int smime_verify_sender(HEADER *h)
{
  char *mbox = NULL, *certfile, tempfname[_POSIX_PATH_MAX];
  FILE *fpout;
  int retval=1;

  mutt_mktemp (tempfname, sizeof (tempfname));
  if (!(fpout = safe_fopen (tempfname, "w")))
  {
    mutt_perror (tempfname);
    return 1;
  }

  if(h->security & ENCRYPT)
    mutt_copy_message (fpout, Context, h,
		       MUTT_CM_DECODE_CRYPT & MUTT_CM_DECODE_SMIME,
		       CH_MIME|CH_WEED|CH_NONEWLINE);
  else
    mutt_copy_message (fpout, Context, h, 0, 0);

  fflush(fpout);
  safe_fclose (&fpout);

  if (h->env->from)
  {
    h->env->from = mutt_expand_aliases (h->env->from); 
    mbox = h->env->from->mailbox; 
  }
  else if (h->env->sender)
  {
    h->env->sender = mutt_expand_aliases (h->env->sender); 
    mbox = h->env->sender->mailbox; 
  }

  if (mbox)
  {
    if ((certfile = smime_extract_signer_certificate(tempfname)))
    {
      mutt_unlink(tempfname);
      if (smime_handle_cert_email (certfile, mbox, 0, NULL, NULL))
      {
	if(isendwin())
         mutt_any_key_to_continue(NULL);
      }
      else
	retval = 0;
      mutt_unlink(certfile);
      FREE (&certfile);
    }
  else 
	mutt_any_key_to_continue(_("no certfile"));
  }
  else 
	mutt_any_key_to_continue(_("no mbox"));

  mutt_unlink(tempfname);
  return retval;
}