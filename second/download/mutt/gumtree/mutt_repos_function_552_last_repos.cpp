void mx_update_context (CONTEXT *ctx, int new_messages)
{
  HEADER *h;
  int msgno;

  for (msgno = ctx->msgcount - new_messages; msgno < ctx->msgcount; msgno++)
  {
    h = ctx->hdrs[msgno];

    if (WithCrypto)
    {
      /* NOTE: this _must_ be done before the check for mailcap! */
      h->security = crypt_query (h->content);
    }

    if (!ctx->pattern)
    {
      ctx->v2r[ctx->vcount] = msgno;
      h->virtual = ctx->vcount++;
    }
    else
      h->virtual = -1;
    h->msgno = msgno;

    if (h->env->supersedes)
    {
      HEADER *h2;

      if (!ctx->id_hash)	
	ctx->id_hash = mutt_make_id_hash (ctx);

      h2 = hash_find (ctx->id_hash, h->env->supersedes);

      /* FREE (&h->env->supersedes); should I ? */
      if (h2)
      {
	h2->superseded = 1;
	if (option (OPTSCORE)) 
	  mutt_score_message (ctx, h2, 1);
      }
    }

    /* add this message to the hash tables */
    if (ctx->id_hash && h->env->message_id)
      hash_insert (ctx->id_hash, h->env->message_id, h);
    if (ctx->subj_hash && h->env->real_subj)
      hash_insert (ctx->subj_hash, h->env->real_subj, h);
    mutt_label_hash_add (ctx, h);

    if (option (OPTSCORE)) 
      mutt_score_message (ctx, h, 0);

    if (h->changed)
      ctx->changed = 1;
    if (h->flagged)
      ctx->flagged++;
    if (h->deleted)
      ctx->deleted++;
    if (!h->read)
    {
      ctx->unread++;
      if (!h->old)
	ctx->new++;
    }
  }
}