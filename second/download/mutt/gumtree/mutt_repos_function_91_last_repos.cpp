static int
generate_body (FILE *tempfp,	/* stream for outgoing message */
	       HEADER *msg,	/* header for outgoing message */
	       int flags,	/* compose mode */
	       CONTEXT *ctx,	/* current mailbox */
	       HEADER *cur)	/* current message */
{
  int i;
  HEADER *h;
  BODY *tmp;

  if (flags & SENDREPLY)
  {
    if ((i = query_quadoption (OPT_INCLUDE, _("Include message in reply?"))) == -1)
      return (-1);

    if (i == MUTT_YES)
    {
      mutt_message _("Including quoted message...");
      if (!cur)
      {
	for (i = 0; i < ctx->vcount; i++)
	{
	  h = ctx->hdrs[ctx->v2r[i]];
	  if (h->tagged)
	  {
	    if (include_reply (ctx, h, tempfp) == -1)
	    {
	      mutt_error _("Could not include all requested messages!");
	      return (-1);
	    }
	    fputc ('\n', tempfp);
	  }
	}
      }
      else
	include_reply (ctx, cur, tempfp);

    }
  }
  else if (flags & SENDFORWARD)
  {
    if ((i = query_quadoption (OPT_MIMEFWD, _("Forward as attachment?"))) == MUTT_YES)
    {
      BODY *last = msg->content;

      mutt_message _("Preparing forwarded message...");
      
      while (last && last->next)
	last = last->next;

      if (cur)
      {
	tmp = mutt_make_message_attach (ctx, cur, 0);
	if (last)
	  last->next = tmp;
	else
	  msg->content = tmp;
      }
      else
      {
	for (i = 0; i < ctx->vcount; i++)
	{
	  if (ctx->hdrs[ctx->v2r[i]]->tagged)
	  {
	    tmp = mutt_make_message_attach (ctx, ctx->hdrs[ctx->v2r[i]], 0);
	    if (last)
	    {
	      last->next = tmp;
	      last = tmp;
	    }
	    else
	      last = msg->content = tmp;
	  }
	}
      }
    }
    else if (i != -1)
    {
      if (cur)
	include_forward (ctx, cur, tempfp);
      else
	for (i=0; i < ctx->vcount; i++)
	  if (ctx->hdrs[ctx->v2r[i]]->tagged)
	    include_forward (ctx, ctx->hdrs[ctx->v2r[i]], tempfp);
    }
    else if (i == -1)
      return -1;
  }
  /* if (WithCrypto && (flags & SENDKEY)) */
  else if ((WithCrypto & APPLICATION_PGP) && (flags & SENDKEY)) 
  {
    BODY *tmp;

    if ((WithCrypto & APPLICATION_PGP)
        && (tmp = crypt_pgp_make_key_attachment (NULL)) == NULL)
      return -1;

    tmp->next = msg->content;
    msg->content = tmp;
  }

  mutt_clear_error ();

  return (0);
}