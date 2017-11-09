BODY *mutt_make_message_attach (CONTEXT *ctx, HEADER *hdr, int attach_msg)
{
  char buffer[LONG_STRING];
  BODY *body;
  FILE *fp;
  int cmflags, chflags;
  int pgp = WithCrypto? hdr->security : 0;

  if (WithCrypto)
  {
    if ((option(OPTMIMEFORWDECODE) || option(OPTFORWDECRYPT)) &&
        (hdr->security & ENCRYPT)) {
      if (!crypt_valid_passphrase(hdr->security))
        return (NULL);
    }
  }

  mutt_mktemp (buffer, sizeof (buffer));
  if ((fp = safe_fopen (buffer, "w+")) == NULL)
    return NULL;

  body = mutt_new_body ();
  body->type = TYPEMESSAGE;
  body->subtype = safe_strdup ("rfc822");
  body->filename = safe_strdup (buffer);
  body->unlink = 1;
  body->use_disp = 0;
  body->disposition = DISPINLINE;
  body->noconv = 1;

  mutt_parse_mime_message (ctx, hdr);

  chflags = CH_XMIT;
  cmflags = 0;

  /* If we are attaching a message, ignore OPTMIMEFORWDECODE */
  if (!attach_msg && option (OPTMIMEFORWDECODE))
  {
    chflags |= CH_MIME | CH_TXTPLAIN;
    cmflags = MUTT_CM_DECODE | MUTT_CM_CHARCONV;
    if ((WithCrypto & APPLICATION_PGP))
      pgp &= ~PGPENCRYPT;
    if ((WithCrypto & APPLICATION_SMIME))
      pgp &= ~SMIMEENCRYPT;
  }
  else if (WithCrypto
           && option (OPTFORWDECRYPT) && (hdr->security & ENCRYPT))
  {
    if ((WithCrypto & APPLICATION_PGP)
        && mutt_is_multipart_encrypted (hdr->content))
    {
      chflags |= CH_MIME | CH_NONEWLINE;
      cmflags = MUTT_CM_DECODE_PGP;
      pgp &= ~PGPENCRYPT;
    }
    else if ((WithCrypto & APPLICATION_PGP)
             && (mutt_is_application_pgp (hdr->content) & PGPENCRYPT))
    {
      chflags |= CH_MIME | CH_TXTPLAIN;
      cmflags = MUTT_CM_DECODE | MUTT_CM_CHARCONV;
      pgp &= ~PGPENCRYPT;
    }
    else if ((WithCrypto & APPLICATION_SMIME)
              && mutt_is_application_smime (hdr->content) & SMIMEENCRYPT)
    {
      chflags |= CH_MIME | CH_TXTPLAIN;
      cmflags = MUTT_CM_DECODE | MUTT_CM_CHARCONV;
      pgp &= ~SMIMEENCRYPT;
    }
  }

  mutt_copy_message (fp, ctx, hdr, cmflags, chflags);

  fflush(fp);
  rewind(fp);

  body->hdr = mutt_new_header();
  body->hdr->offset = 0;
  /* we don't need the user headers here */
  body->hdr->env = mutt_read_rfc822_header(fp, body->hdr, 0, 0);
  if (WithCrypto)
    body->hdr->security = pgp;
  mutt_update_encoding (body);
  body->parts = body->hdr->content;

  safe_fclose (&fp);

  return (body);
}