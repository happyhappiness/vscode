BODY *mutt_make_message_attach (CONTEXT *ctx, HEADER *hdr, int attach_msg)
{
  char buffer[LONG_STRING];
  BODY *body;
  FILE *fp;
  int cmflags, chflags;
#ifdef HAVE_PGP
  int pgp = hdr->pgp;
#endif

#ifdef HAVE_PGP
  if ((option(OPTMIMEFORWDECODE) || option(OPTFORWDECRYPT)) &&
      (hdr->pgp & PGPENCRYPT) && !pgp_valid_passphrase())
    return (NULL);
#endif /* HAVE_PGP */

  mutt_mktemp (buffer);
  if ((fp = safe_fopen (buffer, "w+")) == NULL)
    return NULL;

  body = mutt_new_body ();
  body->type = TYPEMESSAGE;
  body->subtype = safe_strdup ("rfc822");
  body->filename = safe_strdup (buffer);
  body->unlink = 1;
  body->use_disp = 0;
  body->disposition = DISPINLINE;

  mutt_parse_mime_message (ctx, hdr);

  chflags = CH_XMIT;
  cmflags = 0;

  /* If we are attaching a message, ignore OPTMIMEFORWDECODE */
  if (!attach_msg && option (OPTMIMEFORWDECODE))
  {
    chflags |= CH_MIME | CH_TXTPLAIN;
    cmflags = M_CM_DECODE | M_CM_CHARCONV;
#ifdef HAVE_PGP
    pgp &= ~PGPENCRYPT;
#endif
  }
#ifdef HAVE_PGP
  else
    if (option (OPTFORWDECRYPT)
       && (hdr->pgp & PGPENCRYPT))
  {
    if (mutt_is_multipart_encrypted (hdr->content))
    {
      chflags |= CH_MIME | CH_NONEWLINE;
      cmflags = M_CM_DECODE_PGP;
      pgp &= ~PGPENCRYPT;
    }
    else if (mutt_is_application_pgp (hdr->content) & PGPENCRYPT)
    {
      chflags |= CH_MIME | CH_TXTPLAIN;
      cmflags = M_CM_DECODE | M_CM_CHARCONV;
      pgp &= ~PGPENCRYPT;
    }
  }
#endif

  mutt_copy_message (fp, ctx, hdr, cmflags, chflags);
  
  fflush(fp);
  rewind(fp);

  body->hdr = mutt_new_header();
  body->hdr->offset = 0;
  /* we don't need the user headers here */
  body->hdr->env = mutt_read_rfc822_header(fp, body->hdr, 0, 0);
#ifdef HAVE_PGP
  body->hdr->pgp = pgp;
#endif /* HAVE_PGP */
  mutt_update_encoding (body);
  body->parts = body->hdr->content;

  fclose(fp);
  
  return (body);
}