int mutt_prepare_template (FILE *fp, CONTEXT *ctx, HEADER *newhdr, HEADER *hdr,
			       short weed)
{
  MESSAGE *msg = NULL;
  char file[_POSIX_PATH_MAX];
  LIST *p, **q;
  BODY *b;
  FILE *bfp;
  
  int rv = -1;
  STATE s;
  
  memset (&s, 0, sizeof (s));
  
  if (!fp && (msg = mx_open_message (ctx, hdr->msgno)) == NULL)
    return (-1);

  if (!fp) fp = msg->fp;

  bfp = fp;

  /* parse the message header and MIME structure */

  fseek (fp, hdr->offset, 0);
  newhdr->offset = hdr->offset;
  newhdr->env = mutt_read_rfc822_header (fp, newhdr, 1, weed);
  newhdr->content->length = hdr->content->length;
  mutt_parse_part (fp, newhdr->content);

  /* weed user-agent, x-mailer - we don't want them here */
  p = newhdr->env->userhdrs; 
  q = &newhdr->env->userhdrs;

  while (p)
  {
    if (!ascii_strncasecmp (p->data, "x-mailer:", 9) || !ascii_strncasecmp (p->data, "user-agent:", 11))
    {
      *q = p->next;
      p->next = NULL;
      mutt_free_list (&p);
    }
    else
      q = &p->next;

    p = *q;
  }

  safe_free ((void **) &newhdr->env->message_id);
  safe_free ((void **) &newhdr->env->mail_followup_to); /* really? */

#ifdef HAVE_PGP
  /* decrypt pgp/mime encoded messages */
  if ((hdr->pgp & PGPENCRYPT) && 
      mutt_is_multipart_encrypted (newhdr->content))
  {
    newhdr->pgp |= PGPENCRYPT;
    if (!pgp_valid_passphrase())
      goto err;

    mutt_message _("Invoking PGP...");
    if (pgp_decrypt_mime (fp, &bfp, newhdr->content, &b) == -1)
    {
 err:
      mx_close_message (&msg);
      mutt_free_envelope (&newhdr->env);
      mutt_free_body (&newhdr->content);
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
  
  if (mutt_is_multipart_signed (newhdr->content))
  {
    newhdr->pgp |= PGPSIGN;
    
    /* destroy the signature */
    mutt_free_body (&newhdr->content->parts->next);
    newhdr->content = mutt_remove_multipart (newhdr->content);
  }
#endif

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
	s.flags |= M_CHARCONV;
	b->noconv = 0;
      }

      mutt_delete_parameter ("x-mutt-noconv", &b->parameter);
    }

    mutt_adv_mktemp (file, sizeof(file));
    if ((s.fpout = safe_fopen (file, "w")) == NULL)
      goto bail;

    
    mutt_decode_attachment (b, &s);

    if (safe_fclose (&s.fpout) != 0)
      goto bail;

    mutt_str_replace (&b->filename, file);
    b->unlink = 1;

    mutt_stamp_attachment (b);

    mutt_free_body (&b->parts);
    if (b->hdr) b->hdr->content = NULL; /* avoid dangling pointer */
  }

  rv = 0;
  
  bail:
  
  /* that's it. */
  if (bfp != fp) fclose (bfp);
  if (msg) mx_close_message (&msg);
  
  if (rv == -1)
  {
    mutt_free_envelope (&newhdr->env);
    mutt_free_body (&newhdr->content);
  }
  
  return rv;
}