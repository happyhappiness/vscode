void _mutt_set_flag (CONTEXT *ctx, HEADER *h, int flag, int bf, int upd_ctx)
{
  int changed = h->changed;
  int deleted = ctx->deleted;
  int tagged = ctx->tagged;
  int flagged = ctx->flagged;
  int update = 0;

  if (ctx->readonly && flag != MUTT_TAG)
    return; /* don't modify anything if we are read-only */

  switch (flag)
  {
    case MUTT_DELETE:

      if (!mutt_bit_isset(ctx->rights,MUTT_ACL_DELETE))
	return;

      if (bf)
      {
	if (!h->deleted && !ctx->readonly
	    && (!h->flagged || !option(OPTFLAGSAFE)))
	{
	  h->deleted = 1;
          update = 1;
	  if (upd_ctx) ctx->deleted++;
#ifdef USE_IMAP
          /* deleted messages aren't treated as changed elsewhere so that the
           * purge-on-sync option works correctly. This isn't applicable here */
          if (ctx && ctx->magic == MUTT_IMAP)
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
        update = 1;
	if (upd_ctx) ctx->deleted--;
#ifdef USE_IMAP
        /* see my comment above */
	if (ctx->magic == MUTT_IMAP) 
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
	if (ctx->magic == MUTT_MAILDIR && upd_ctx && h->trash)
	  ctx->changed = 1;
      }
      break;

    case MUTT_PURGE:

      if (!mutt_bit_isset(ctx->rights,MUTT_ACL_DELETE))
        return;

      if (bf)
      {
        if (!h->purge && !ctx->readonly)
          h->purge = 1;
      }
      else if (h->purge)
        h->purge = 0;
      break;

    case MUTT_NEW:

      if (!mutt_bit_isset(ctx->rights,MUTT_ACL_SEEN))
	return;

      if (bf)
      {
	if (h->read || h->old)
	{
          update = 1;
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
        update = 1;
	if (!h->old)
	  if (upd_ctx) ctx->new--;
	h->read = 1;
	if (upd_ctx) ctx->unread--;
	h->changed = 1;
	if (upd_ctx) ctx->changed = 1;
      }
      break;

    case MUTT_OLD:

      if (!mutt_bit_isset(ctx->rights,MUTT_ACL_SEEN))
	return;

      if (bf)
      {
	if (!h->old)
	{
          update = 1;
	  h->old = 1;
	  if (!h->read)
	    if (upd_ctx) ctx->new--;
	  h->changed = 1;
	  if (upd_ctx) ctx->changed = 1;
	}
      }
      else if (h->old)
      {
        update = 1;
	h->old = 0;
	if (!h->read)
	  if (upd_ctx) ctx->new++;
	h->changed = 1;
	if (upd_ctx) ctx->changed = 1;
      }
      break;

    case MUTT_READ:

      if (!mutt_bit_isset(ctx->rights,MUTT_ACL_SEEN))
	return;

      if (bf)
      {
	if (!h->read)
	{
          update = 1;
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
        update = 1;
	h->read = 0;
	if (upd_ctx) ctx->unread++;
	if (!h->old)
	  if (upd_ctx) ctx->new++;
	h->changed = 1;
	if (upd_ctx) ctx->changed = 1;
      }
      break;

    case MUTT_REPLIED:

      if (!mutt_bit_isset(ctx->rights,MUTT_ACL_WRITE))
	return;

      if (bf)
      {
	if (!h->replied)
	{
          update = 1;
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
        update = 1;
	h->replied = 0;
	h->changed = 1;
	if (upd_ctx) ctx->changed = 1;
      }
      break;

    case MUTT_FLAG:

      if (!mutt_bit_isset(ctx->rights,MUTT_ACL_WRITE))
	return;

      if (bf)
      {
	if (!h->flagged)
	{
          update = 1;
	  h->flagged = bf;
	  if (upd_ctx) ctx->flagged++;
	  h->changed = 1;
	  if (upd_ctx) ctx->changed = 1;
	}
      }
      else if (h->flagged)
      {
        update = 1;
	h->flagged = 0;
	if (upd_ctx) ctx->flagged--;
	h->changed = 1;
	if (upd_ctx) ctx->changed = 1;
      }
      break;

    case MUTT_TAG:
      if (bf)
      {
	if (!h->tagged)
	{
          update = 1;
	  h->tagged = 1;
	  if (upd_ctx) ctx->tagged++;
	}
      }
      else if (h->tagged)
      {
        update = 1;
	h->tagged = 0;
	if (upd_ctx) ctx->tagged--;
      }
      break;
  }

  if (update)
  {
    mutt_set_header_color(ctx, h);
#ifdef USE_SIDEBAR
    mutt_set_current_menu_redraw (REDRAW_SIDEBAR);
#endif
  }

  /* if the message status has changed, we need to invalidate the cached
   * search results so that any future search will match the current status
   * of this message and not what it was at the time it was last searched.
   */
  if (h->searched && (changed != h->changed || deleted != ctx->deleted || tagged != ctx->tagged || flagged != ctx->flagged))
    h->searched = 0;
}