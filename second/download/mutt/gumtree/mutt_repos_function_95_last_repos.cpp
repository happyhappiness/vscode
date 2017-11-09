static int send_message (HEADER *msg)
{  
  char tempfile[_POSIX_PATH_MAX];
  FILE *tempfp;
  int i;
#ifdef USE_SMTP
  short old_write_bcc;
#endif
  
  /* Write out the message in MIME form. */
  mutt_mktemp (tempfile, sizeof (tempfile));
  if ((tempfp = safe_fopen (tempfile, "w")) == NULL)
    return (-1);

#ifdef USE_SMTP
  old_write_bcc = option (OPTWRITEBCC);
  if (SmtpUrl)
    unset_option (OPTWRITEBCC);
#endif
#ifdef MIXMASTER
  mutt_write_rfc822_header (tempfp, msg->env, msg->content, 0, msg->chain ? 1 : 0);
#endif
#ifndef MIXMASTER
  mutt_write_rfc822_header (tempfp, msg->env, msg->content, 0, 0);
#endif
#ifdef USE_SMTP
  if (old_write_bcc)
    set_option (OPTWRITEBCC);
#endif
  
  fputc ('\n', tempfp); /* tie off the header. */

  if ((mutt_write_mime_body (msg->content, tempfp) == -1))
  {
    safe_fclose (&tempfp);
    unlink (tempfile);
    return (-1);
  }
  
  if (fclose (tempfp) != 0)
  {
    mutt_perror (tempfile);
    unlink (tempfile);
    return (-1);
  }

#ifdef MIXMASTER
  if (msg->chain)
    return mix_send_message (msg->chain, tempfile);
#endif

#if USE_SMTP
  if (SmtpUrl)
      return mutt_smtp_send (msg->env->from, msg->env->to, msg->env->cc,
                             msg->env->bcc, tempfile,
                             (msg->content->encoding == ENC8BIT));
#endif /* USE_SMTP */

  i = mutt_invoke_sendmail (msg->env->from, msg->env->to, msg->env->cc, 
			    msg->env->bcc, tempfile,
                            (msg->content->encoding == ENC8BIT));
  return (i);
}