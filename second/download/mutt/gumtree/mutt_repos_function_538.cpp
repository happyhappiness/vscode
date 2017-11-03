void mx_update_tables(CONTEXT *ctx, int committing)
{
  int i, j;
  
  /* update memory to reflect the new state of the mailbox */
  ctx->vcount = 0;
  ctx->vsize = 0;
  ctx->tagged = 0;
  ctx->deleted = 0;
  ctx->new = 0;
  ctx->unread = 0;
  ctx->changed = 0;
  ctx->flagged = 0;
#define this_body ctx->hdrs[j]->content
  for (i = 0, j = 0; i < ctx->msgcount; i++)
  {
    if ((committing && (!ctx->hdrs[i]->deleted || 
			(ctx->magic == MUTT_MAILDIR && option (OPTMAILDIRTRASH)))) ||
	(!committing && ctx->hdrs[i]->active))
    {
      if (i != j)
      {
	ctx->hdrs[j] = ctx->hdrs[i];
	ctx->hdrs[i] = NULL;
      }
      ctx->hdrs[j]->msgno = j;
      if (ctx->hdrs[j]->virtual != -1)
      {
	ctx->v2r[ctx->vcount] = j;
	ctx->hdrs[j]->virtual = ctx->vcount++;
	ctx->vsize += this_body->length + this_body->offset -
	  this_body->hdr_offset;
      }

      if (committing)
	ctx->hdrs[j]->changed = 0;
      else if (ctx->hdrs[j]->changed)
	ctx->changed++;
      
      if (!committing || (ctx->magic == MUTT_MAILDIR && option (OPTMAILDIRTRASH)))
      {
	if (ctx->hdrs[j]->deleted)
	  ctx->deleted++;
      }

      if (ctx->hdrs[j]->tagged)
	ctx->tagged++;
      if (ctx->hdrs[j]->flagged)
	ctx->flagged++;
      if (!ctx->hdrs[j]->read)
      { 
	ctx->unread++;
	if (!ctx->hdrs[j]->old)
	  ctx->new++;
      } 

      j++;
    }
    else
    {
      if (ctx->magic == MUTT_MH || ctx->magic == MUTT_MAILDIR)
	ctx->size -= (ctx->hdrs[i]->content->length +
		      ctx->hdrs[i]->content->offset -
		      ctx->hdrs[i]->content->hdr_offset);
      /* remove message from the hash tables */
      if (ctx->subj_hash && ctx->hdrs[i]->env->real_subj)
	hash_delete (ctx->subj_hash, ctx->hdrs[i]->env->real_subj, ctx->hdrs[i], NULL);
      if (ctx->id_hash && ctx->hdrs[i]->env->message_id)
	hash_delete (ctx->id_hash, ctx->hdrs[i]->env->message_id, ctx->hdrs[i], NULL);
      /* The path mx_check_mailbox() -> imap_check_mailbox() ->
       *          imap_expunge_mailbox() -> mx_update_tables()
       * can occur before a call to mx_sync_mailbox(), resulting in
       * last_tag being stale if it's not reset here.
       */
      if (ctx->last_tag == ctx->hdrs[i])
        ctx->last_tag = NULL;
      mutt_free_header (&ctx->hdrs[i]);
    }
  }
#undef this_body
  ctx->msgcount = j;
}