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
