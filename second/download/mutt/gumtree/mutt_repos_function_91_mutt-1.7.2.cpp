static int
envelope_defaults (ENVELOPE *env, CONTEXT *ctx, HEADER *cur, int flags)
{
  ENVELOPE *curenv = NULL;
  int i = 0, tag = 0;

  if (!cur)
  {
    tag = 1;
    for (i = 0; i < ctx->vcount; i++)
      if (ctx->hdrs[ctx->v2r[i]]->tagged)
      {
	cur = ctx->hdrs[ctx->v2r[i]];
	curenv = cur->env;
	break;
      }

    if (!cur)
    {
      /* This could happen if the user tagged some messages and then did
       * a limit such that none of the tagged message are visible.
       */
      mutt_error _("No tagged messages are visible!");
      return (-1);
    }
  }
  else
    curenv = cur->env;

  if (flags & SENDREPLY)
  {
    if (tag)
    {
      HEADER *h;

      for (i = 0; i < ctx->vcount; i++)
      {
	h = ctx->hdrs[ctx->v2r[i]];
	if (h->tagged && mutt_fetch_recips (env, h->env, flags) == -1)
	  return -1;
      }
    }
    else if (mutt_fetch_recips (env, curenv, flags) == -1)
      return -1;

    if ((flags & SENDLISTREPLY) && !env->to)
    {
      mutt_error _("No mailing lists found!");
      return (-1);
    }

    mutt_make_misc_reply_headers (env, ctx, cur, curenv);
    mutt_make_reference_headers (tag ? NULL : curenv, env, ctx);
  }
  else if (flags & SENDFORWARD)
    mutt_make_forward_subject (env, ctx, cur);

  return (0);
}