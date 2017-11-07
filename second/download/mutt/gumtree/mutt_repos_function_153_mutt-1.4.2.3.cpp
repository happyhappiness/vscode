void _mutt_set_flag (CONTEXT *ctx, HEADER *h, int flag, int bf, int upd_ctx)
{
  int changed = h->changed;
  int deleted = ctx->deleted;
  int tagged = ctx->tagged;

  if (ctx->readonly && flag != M_TAG)
    return; /* don't modify anything if we are read-only */

  switch (flag)
  {
    case M_DELETE:
      if (bf)
      {
	if (!h->deleted)
	{
	  h->deleted = 1;
	  if (upd_ctx) ctx->deleted++;
#ifdef USE_IMAP
          /* deleted messages aren't treated as changed elsewhere so that the
           * purge-on-sync option works correctly. This isn't applicable here */
          if (ctx->magic == M_IMAP)
          {
            h->changed = 1;
	    if (upd_ctx) ctx->changed = 1;
          }
#endif
	}
      }
      else if (h->deleted)
      {
	h->deleted = 0;
	if (upd_ctx) ctx->deleted--;
#ifdef USE_IMAP
        /* see my comment above */
	if (ctx->magic == M_IMAP) 
	{
	  h->changed = 1;
	  if (upd_ctx) ctx->changed = 1;
	}
#endif
	/* 
	 * If the user undeletes a message which is marked as
	 * "trash" in the maildir folder on disk, the folder has
	 * been changed, and is marked accordingly.  However, we do
	 * _not_ mark the message itself changed, because trashing
	 * is checked in specific code in the maildir folder
	 * driver. 
	 */
	if (ctx->magic == M_MAILDIR && upd_ctx && h->trash)
	  ctx->changed = 1;
      }
      break;

    case M_NEW:
      if (bf)
      {
	if (h->read || h->old)
	{
	  h->old = 0;
	  if (upd_ctx) ctx->new++;
	  if (h->read)
	  {
	    h->read = 0;
	    if (upd_ctx) ctx->unread++;
	  }
	  h->changed = 1;
	  if (upd_ctx) ctx->changed = 1;
	}
      }
      else if (!h->read)
      {
	if (!h->old)
	  if (upd_ctx) ctx->new--;
	h->read = 1;
	if (upd_ctx) ctx->unread--;
	h->changed = 1;
	if (upd_ctx) ctx->changed = 1;
      }
      break;

    case M_OLD:
      if (bf)
      {
	if (!h->old)
	{
	  h->old = 1;
	  if (!h->read)
	    if (upd_ctx) ctx->new--;
	  h->changed = 1;
	  if (upd_ctx) ctx->changed = 1;
	}
      }
      else if (h->old)
      {
	h->old = 0;
	if (!h->read)
	  if (upd_ctx) ctx->new++;
	h->changed = 1;
	if (upd_ctx) ctx->changed = 1;
      }
      break;

    case M_READ:
      if (bf)
      {
	if (!h->read)
	{
	  h->read = 1;
	  if (upd_ctx) ctx->unread--;
	  if (!h->old)
	    if (upd_ctx) ctx->new--;
	  h->changed = 1;
	  if (upd_ctx) ctx->changed = 1;
	}
      }
      else if (h->read)
      {
	h->read = 0;
	if (upd_ctx) ctx->unread++;
	if (!h->old)
	  if (upd_ctx) ctx->new++;
	h->changed = 1;
	if (upd_ctx) ctx->changed = 1;
      }
      break;

    case M_REPLIED:
      if (bf)
      {
	if (!h->replied)
	{
	  h->replied = 1;
	  if (!h->read)
	  {
	    h->read = 1;
	    if (upd_ctx) ctx->unread--;
	    if (!h->old)
	      if (upd_ctx) ctx->new--;
	  }
	  h->changed = 1;
	  if (upd_ctx) ctx->changed = 1;
	}
      }
      else if (h->replied)
      {
	h->replied = 0;
	h->changed = 1;
	if (upd_ctx) ctx->changed = 1;
      }
      break;

    case M_FLAG:
      if (bf)
      {
	if (!h->flagged)
	{
	  h->flagged = bf;
	  if (upd_ctx) ctx->flagged++;
	  h->changed = 1;
	  if (upd_ctx) ctx->changed = 1;
	}
      }
      else if (h->flagged)
      {
	h->flagged = 0;
	if (upd_ctx) ctx->flagged--;
	h->changed = 1;
	if (upd_ctx) ctx->changed = 1;
      }
      break;

    case M_TAG:
      if (bf)
      {
	if (!h->tagged)
	{
	  h->tagged = 1;
	  if (upd_ctx) ctx->tagged++;
	}
      }
      else if (h->tagged)
      {
	h->tagged = 0;
	if (upd_ctx) ctx->tagged--;
      }
      break;
  }

  mutt_set_header_color(ctx, h);

  /* if the message status has changed, we need to invalidate the cached
   * search results so that any future search will match the current status
   * of this message and not what it was at the time it was last searched.
   */
  if (h->searched && (changed != h->changed || deleted != ctx->deleted || tagged != ctx->tagged))
    h->searched = 0;
}