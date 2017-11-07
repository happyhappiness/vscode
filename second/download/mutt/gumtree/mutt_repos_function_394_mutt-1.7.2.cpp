int mutt_get_postponed (CONTEXT *ctx, HEADER *hdr, HEADER **cur, char *fcc, size_t fcclen)
{
  HEADER *h;
  int code = SENDPOSTPONED;
  LIST *tmp;
  LIST *last = NULL;
  LIST *next;
  const char *p;
  int opt_delete;

  if (!Postponed)
    return (-1);

  if ((PostContext = mx_open_mailbox (Postponed, MUTT_NOSORT, NULL)) == NULL)
  {
    PostCount = 0;
    mutt_error _("No postponed messages.");
    return (-1);
  }

  if (! PostContext->msgcount)
  {
    PostCount = 0;
    mx_close_mailbox (PostContext, NULL);
    FREE (&PostContext);
    mutt_error _("No postponed messages.");
    return (-1);
  }

  if (PostContext->msgcount == 1)
  {
    /* only one message, so just use that one. */
    h = PostContext->hdrs[0];
  }
  else if ((h = select_msg ()) == NULL)
  {
    mx_close_mailbox (PostContext, NULL);
    FREE (&PostContext);
    return (-1);
  }

  if (mutt_prepare_template (NULL, PostContext, hdr, h, 0) < 0)
  {
    mx_fastclose_mailbox (PostContext);
    FREE (&PostContext);
    return (-1);
  }

  /* finished with this message, so delete it. */
  mutt_set_flag (PostContext, h, MUTT_DELETE, 1);
  mutt_set_flag (PostContext, h, MUTT_PURGE, 1);

  /* update the count for the status display */
  PostCount = PostContext->msgcount - PostContext->deleted;

  /* avoid the "purge deleted messages" prompt */
  opt_delete = quadoption (OPT_DELETE);
  set_quadoption (OPT_DELETE, MUTT_YES);
  mx_close_mailbox (PostContext, NULL);
  set_quadoption (OPT_DELETE, opt_delete);

  FREE (&PostContext);

  for (tmp = hdr->env->userhdrs; tmp; )
  {
    if (ascii_strncasecmp ("X-Mutt-References:", tmp->data, 18) == 0)
    {
      if (ctx)
      {
	/* if a mailbox is currently open, look to see if the orignal message
	   the user attempted to reply to is in this mailbox */
	p = skip_email_wsp(tmp->data + 18);
	if (!ctx->id_hash)
	  ctx->id_hash = mutt_make_id_hash (ctx);
	*cur = hash_find (ctx->id_hash, p);
      }

      /* Remove the X-Mutt-References: header field. */
      next = tmp->next;
      if (last)
	last->next = tmp->next;
      else
	hdr->env->userhdrs = tmp->next;
      tmp->next = NULL;
      mutt_free_list (&tmp);
      tmp = next;
      if (*cur)
	code |= SENDREPLY;
    }
    else if (ascii_strncasecmp ("X-Mutt-Fcc:", tmp->data, 11) == 0)
    {
      p = skip_email_wsp(tmp->data + 11);
      strfcpy (fcc, p, fcclen);
      mutt_pretty_mailbox (fcc, fcclen);

      /* remove the X-Mutt-Fcc: header field */
      next = tmp->next;
      if (last)
	last->next = tmp->next;
      else
	hdr->env->userhdrs = tmp->next;
      tmp->next = NULL;
      mutt_free_list (&tmp);
      tmp = next;
     /* note that x-mutt-fcc was present.  we do this because we want to add a
      * default fcc if the header was missing, but preserve the request of the
      * user to not make a copy if the header field is present, but empty.
      * see http://dev.mutt.org/trac/ticket/3653
      */
      code |= SENDPOSTPONEDFCC;
    }
    else if ((WithCrypto & APPLICATION_PGP)
             && (mutt_strncmp ("Pgp:", tmp->data, 4) == 0 /* this is generated
						       * by old mutt versions
						       */
                 || mutt_strncmp ("X-Mutt-PGP:", tmp->data, 11) == 0))
    {
      hdr->security = mutt_parse_crypt_hdr (strchr (tmp->data, ':') + 1, 1,
					    APPLICATION_PGP);
      hdr->security |= APPLICATION_PGP;

      /* remove the pgp field */
      next = tmp->next;
      if (last)
	last->next = tmp->next;
      else
	hdr->env->userhdrs = tmp->next;
      tmp->next = NULL;
      mutt_free_list (&tmp);
      tmp = next;
    }
    else if ((WithCrypto & APPLICATION_SMIME)
             && mutt_strncmp ("X-Mutt-SMIME:", tmp->data, 13) == 0)
    {
      hdr->security = mutt_parse_crypt_hdr (strchr (tmp->data, ':') + 1, 1,
					    APPLICATION_SMIME);
      hdr->security |= APPLICATION_SMIME;

      /* remove the smime field */
      next = tmp->next;
      if (last)
	last->next = tmp->next;
      else
	hdr->env->userhdrs = tmp->next;
      tmp->next = NULL;
      mutt_free_list (&tmp);
      tmp = next;
    }

#ifdef MIXMASTER
    else if (mutt_strncmp ("X-Mutt-Mix:", tmp->data, 11) == 0)
    {
      char *t;
      mutt_free_list (&hdr->chain);

      t = strtok (tmp->data + 11, " \t\n");
      while (t)
      {
	hdr->chain = mutt_add_list (hdr->chain, t);
	t = strtok (NULL, " \t\n");
      }

      next = tmp->next;
      if (last)
	last->next = tmp->next;
      else
	hdr->env->userhdrs = tmp->next;
      tmp->next = NULL;
      mutt_free_list (&tmp);
      tmp = next;
    }
#endif

    else
    {
      last = tmp;
      tmp = tmp->next;
    }
  }

  if (option (OPTCRYPTOPPORTUNISTICENCRYPT))
    crypt_opportunistic_encrypt (hdr);

  return (code);
}