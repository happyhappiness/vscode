int mutt_prepare_template (FILE *fp, CONTEXT *ctx, HEADER *newhdr, HEADER *hdr,
			       short weed)
{
  MESSAGE *msg = NULL;
  char file[_POSIX_PATH_MAX];
  BODY *b;
  FILE *bfp;
  int rv = -1;
  STATE s;
  int sec_type;

  memset (&s, 0, sizeof (s));

  if (!fp && (msg = mx_open_message (ctx, hdr->msgno)) == NULL)
    return (-1);

  if (!fp) fp = msg->fp;

  bfp = fp;

  /* parse the message header and MIME structure */

  fseeko (fp, hdr->offset, 0);
  newhdr->offset = hdr->offset;
  newhdr->env = mutt_read_rfc822_header (fp, newhdr, 1, weed);
  newhdr->content->length = hdr->content->length;
  mutt_parse_part (fp, newhdr->content);

  /* If message_id is set, then we are resending a message and don't want
   * message_id or mail_followup_to. Otherwise, we are resuming a
   * postponed message, and want to keep the mail_followup_to.
   */
  if (newhdr->env->message_id != NULL)
  {
    FREE (&newhdr->env->message_id);
    FREE (&newhdr->env->mail_followup_to);
  }

  /* decrypt pgp/mime encoded messages */

  if ((WithCrypto & APPLICATION_PGP) &&
      (sec_type = mutt_is_multipart_encrypted (newhdr->content)))
  {
    newhdr->security |= sec_type;
    if (!crypt_valid_passphrase (sec_type))
      goto err;

    mutt_message _("Decrypting message...");
    if ((crypt_pgp_decrypt_mime (fp, &bfp, newhdr->content, &b) == -1)
	|| b == NULL)
    {
 err:
      mx_close_message (ctx, &msg);
      mutt_free_envelope (&newhdr->env);
      mutt_free_body (&newhdr->content);
      mutt_error _("Decryption failed.");
      return -1;
    }

    mutt_free_body (&newhdr->content);
    newhdr->content = b;

    mutt_clear_error ();
  }

  /*
   * remove a potential multipart/signed layer - useful when
   * resending messages
   */

  if (WithCrypto && mutt_is_multipart_signed (newhdr->content))
  {
    newhdr->security |= SIGN;
    if ((WithCrypto & APPLICATION_PGP)
        && ascii_strcasecmp (mutt_get_parameter ("protocol", newhdr->content->parameter), "application/pgp-signature") == 0)
      newhdr->security |= APPLICATION_PGP;
    else if ((WithCrypto & APPLICATION_SMIME))
      newhdr->security |= APPLICATION_SMIME;

    /* destroy the signature */
    mutt_free_body (&newhdr->content->parts->next);
    newhdr->content = mutt_remove_multipart (newhdr->content);
  }


  /*
   * We don't need no primary multipart.
   * Note: We _do_ preserve messages!
   *
   * XXX - we don't handle multipart/alternative in any
   * smart way when sending messages.  However, one may
   * consider this a feature.
   *
   */

  if (newhdr->content->type == TYPEMULTIPART)
    newhdr->content = mutt_remove_multipart (newhdr->content);

  s.fpin = bfp;

  /* create temporary files for all attachments */
  for (b = newhdr->content; b; b = b->next)
  {

    /* what follows is roughly a receive-mode variant of
     * mutt_get_tmp_attachment () from muttlib.c
     */

    file[0] = '\0';
    if (b->filename)
    {
      strfcpy (file, b->filename, sizeof (file));
      b->d_filename = safe_strdup (b->filename);
    }
    else
    {
      /* avoid Content-Disposition: header with temporary filename */
      b->use_disp = 0;
    }

    /* set up state flags */

    s.flags = 0;

    if (b->type == TYPETEXT)
    {
      if (!ascii_strcasecmp ("yes", mutt_get_parameter ("x-mutt-noconv", b->parameter)))
	b->noconv = 1;
      else
      {
	s.flags |= MUTT_CHARCONV;
	b->noconv = 0;
      }

      mutt_delete_parameter ("x-mutt-noconv", &b->parameter);
    }

    mutt_adv_mktemp (file, sizeof(file));
    if ((s.fpout = safe_fopen (file, "w")) == NULL)
      goto bail;


    if ((WithCrypto & APPLICATION_PGP) &&
	((sec_type = mutt_is_application_pgp (b)) & (ENCRYPT|SIGN)))
    {
      mutt_body_handler (b, &s);

      newhdr->security |= sec_type;

      b->type = TYPETEXT;
      mutt_str_replace (&b->subtype, "plain");
      mutt_delete_parameter ("x-action", &b->parameter);
    }
    else if ((WithCrypto & APPLICATION_SMIME) &&
             ((sec_type = mutt_is_application_smime (b)) & (ENCRYPT|SIGN)))
    {
      mutt_body_handler (b, &s);

      newhdr->security |= sec_type;
      b->type = TYPETEXT;
      mutt_str_replace (&b->subtype, "plain");
    }
    else
      mutt_decode_attachment (b, &s);

    if (safe_fclose (&s.fpout) != 0)
      goto bail;

    mutt_str_replace (&b->filename, file);
    b->unlink = 1;

    mutt_stamp_attachment (b);

    mutt_free_body (&b->parts);
    if (b->hdr) b->hdr->content = NULL; /* avoid dangling pointer */
  }

  /* Fix encryption flags. */

  /* No inline if multipart. */
  if (WithCrypto && (newhdr->security & INLINE) && newhdr->content->next)
    newhdr->security &= ~INLINE;

  /* Do we even support multiple mechanisms? */
  newhdr->security &= WithCrypto | ~(APPLICATION_PGP|APPLICATION_SMIME);

  /* Theoretically, both could be set. Take the one the user wants to set by default. */
  if ((newhdr->security & APPLICATION_PGP) && (newhdr->security & APPLICATION_SMIME))
  {
    if (option (OPTSMIMEISDEFAULT))
      newhdr->security &= ~APPLICATION_PGP;
    else
      newhdr->security &= ~APPLICATION_SMIME;
  }

  rv = 0;

  bail:

  /* that's it. */
  if (bfp != fp) safe_fclose (&bfp);
  if (msg) mx_close_message (ctx, &msg);

  if (rv == -1)
  {
    mutt_free_envelope (&newhdr->env);
    mutt_free_body (&newhdr->content);
  }

  return rv;
}