static int mh_sync_message (CONTEXT * ctx, int msgno)
{
  HEADER *h = ctx->hdrs[msgno];

  if (h->attach_del || h->xlabel_changed ||
      (h->env && (h->env->refs_changed || h->env->irt_changed)))
    if (mh_rewrite_message (ctx, msgno) != 0)
      return -1;

  return 0;
}