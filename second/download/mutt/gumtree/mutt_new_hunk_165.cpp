
    Sort = SORT_ORDER;
    qsort (ctx->hdrs, ctx->msgcount, sizeof (HEADER*),
           mutt_get_sort_func (SORT_ORDER));
  }

  rc = sync_helper (idata, M_ACL_DELETE, M_DELETED, "\\Deleted");
  if (rc >= 0)
    rc |= sync_helper (idata, M_ACL_WRITE, M_FLAG, "\\Flagged");
  if (rc >= 0)
    rc |= sync_helper (idata, M_ACL_WRITE, M_OLD, "Old");
  if (rc >= 0)
    rc |= sync_helper (idata, M_ACL_SEEN, M_READ, "\\Seen");
  if (rc >= 0)
    rc |= sync_helper (idata, M_ACL_WRITE, M_REPLIED, "\\Answered");

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
      if (mutt_yesorno (_("Error saving flags. Close anyway?"), 0) == M_YES)
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
