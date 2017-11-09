int imap_sync_mailbox (CONTEXT* ctx, int expunge, int* index_hint)
{
  IMAP_DATA* idata;
  CONTEXT* appendctx = NULL;
  HEADER* h;
  HEADER** hdrs = NULL;
  int oldsort;
  int n;
  int rc;

  idata = (IMAP_DATA*) ctx->data;

  if (idata->state < IMAP_SELECTED)
  {
    dprint (2, (debugfile, "imap_sync_mailbox: no mailbox selected\n"));
    return -1;
  }

  /* This function is only called when the calling code expects the context
   * to be changed. */
  imap_allow_reopen (ctx);

  if ((rc = imap_check_mailbox (ctx, index_hint, 0)) != 0)
    return rc;

  /* if we are expunging anyway, we can do deleted messages very quickly... */
  if (expunge && mutt_bit_isset (ctx->rights, MUTT_ACL_DELETE))
  {
    if ((rc = imap_exec_msgset (idata, "UID STORE", "+FLAGS.SILENT (\\Deleted)",
                                MUTT_DELETED, 1, 0)) < 0)
    {
      mutt_error (_("Expunge failed"));
      mutt_sleep (1);
      goto out;
    }

    if (rc > 0)
    {
      /* mark these messages as unchanged so second pass ignores them. Done
       * here so BOGUS UW-IMAP 4.7 SILENT FLAGS updates are ignored. */
      for (n = 0; n < ctx->msgcount; n++)
        if (ctx->hdrs[n]->deleted && ctx->hdrs[n]->changed)
          ctx->hdrs[n]->active = 0;
      mutt_message (_("Marking %d messages deleted..."), rc);
    }
  }

#if USE_HCACHE
  idata->hcache = imap_hcache_open (idata, NULL);
#endif

  /* save messages with real (non-flag) changes */
  for (n = 0; n < ctx->msgcount; n++)
  {
    h = ctx->hdrs[n];

    if (h->deleted)
    {
      imap_cache_del (idata, h);
#if USE_HCACHE
      imap_hcache_del (idata, HEADER_DATA(h)->uid);
#endif
    }

    if (h->active && h->changed)
    {
#if USE_HCACHE
      imap_hcache_put (idata, h);
#endif
      /* if the message has been rethreaded or attachments have been deleted
       * we delete the message and reupload it.
       * This works better if we're expunging, of course. */
      if ((h->env && (h->env->refs_changed || h->env->irt_changed)) ||
	  h->attach_del || h->xlabel_changed)
      {
        mutt_message (_("Saving changed messages... [%d/%d]"), n+1,
                      ctx->msgcount);
	if (!appendctx)
	  appendctx = mx_open_mailbox (ctx->path, MUTT_APPEND | MUTT_QUIET, NULL);
	if (!appendctx)
	  dprint (1, (debugfile, "imap_sync_mailbox: Error opening mailbox in append mode\n"));
	else
	  _mutt_save_message (h, appendctx, 1, 0, 0);
	h->xlabel_changed = 0;
      }
    }
  }

#if USE_HCACHE
  imap_hcache_close (idata);
#endif

  /* presort here to avoid doing 10 resorts in imap_exec_msgset */
  oldsort = Sort;
  if (Sort != SORT_ORDER)
  {
    hdrs = ctx->hdrs;
    ctx->hdrs = safe_malloc (ctx->msgcount * sizeof (HEADER*));
    memcpy (ctx->hdrs, hdrs, ctx->msgcount * sizeof (HEADER*));

    Sort = SORT_ORDER;
    qsort (ctx->hdrs, ctx->msgcount, sizeof (HEADER*),
           mutt_get_sort_func (SORT_ORDER));
  }

  rc = sync_helper (idata, MUTT_ACL_DELETE, MUTT_DELETED, "\\Deleted");
  if (rc >= 0)
    rc |= sync_helper (idata, MUTT_ACL_WRITE, MUTT_FLAG, "\\Flagged");
  if (rc >= 0)
    rc |= sync_helper (idata, MUTT_ACL_WRITE, MUTT_OLD, "Old");
  if (rc >= 0)
    rc |= sync_helper (idata, MUTT_ACL_SEEN, MUTT_READ, "\\Seen");
  if (rc >= 0)
    rc |= sync_helper (idata, MUTT_ACL_WRITE, MUTT_REPLIED, "\\Answered");

  if (oldsort != Sort)
  {
    Sort = oldsort;
    FREE (&ctx->hdrs);
    ctx->hdrs = hdrs;
  }

  /* Flush the queued flags if any were changed in sync_helper. */
  if (rc > 0)
    if (imap_exec (idata, NULL, 0) != IMAP_CMD_OK)
      rc = -1;

  if (rc < 0)
  {
    if (ctx->closing)
    {
      if (mutt_yesorno (_("Error saving flags. Close anyway?"), 0) == MUTT_YES)
      {
        rc = 0;
        idata->state = IMAP_AUTHENTICATED;
        goto out;
      }
    }
    else
      mutt_error _("Error saving flags");
    rc = -1;
    goto out;
  }

  /* Update local record of server state to reflect the synchronization just
   * completed.  imap_read_headers always overwrites hcache-origin flags, so
   * there is no need to mutate the hcache after flag-only changes. */
  for (n = 0; n < ctx->msgcount; n++)
  {
    HEADER_DATA(ctx->hdrs[n])->deleted = ctx->hdrs[n]->deleted;
    HEADER_DATA(ctx->hdrs[n])->flagged = ctx->hdrs[n]->flagged;
    HEADER_DATA(ctx->hdrs[n])->old = ctx->hdrs[n]->old;
    HEADER_DATA(ctx->hdrs[n])->read = ctx->hdrs[n]->read;
    HEADER_DATA(ctx->hdrs[n])->replied = ctx->hdrs[n]->replied;
    ctx->hdrs[n]->changed = 0;
  }
  ctx->changed = 0;

  /* We must send an EXPUNGE command if we're not closing. */
  if (expunge && !(ctx->closing) &&
      mutt_bit_isset(ctx->rights, MUTT_ACL_DELETE))
  {
    mutt_message _("Expunging messages from server...");
    /* Set expunge bit so we don't get spurious reopened messages */
    idata->reopen |= IMAP_EXPUNGE_EXPECTED;
    if (imap_exec (idata, "EXPUNGE", 0) != 0)
    {
      idata->reopen &= ~IMAP_EXPUNGE_EXPECTED;
      imap_error (_("imap_sync_mailbox: EXPUNGE failed"), idata->buf);
      rc = -1;
      goto out;
    }
    idata->reopen &= ~IMAP_EXPUNGE_EXPECTED;
  }

  if (expunge && ctx->closing)
  {
    imap_exec (idata, "CLOSE", IMAP_CMD_QUEUE);
    idata->state = IMAP_AUTHENTICATED;
  }

  if (option (OPTMESSAGECACHECLEAN))
    imap_cache_clean (idata);

  rc = 0;

 out:
  if (appendctx)
  {
    mx_fastclose_mailbox (appendctx);
    FREE (&appendctx);
  }
  return rc;
}