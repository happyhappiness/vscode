int imap_exec_msgset (IMAP_DATA* idata, const char* pre, const char* post,
                      int flag, int changed, int invert)
{
  HEADER** hdrs = NULL;
  short oldsort;
  BUFFER* cmd;
  int pos;
  int rc;
  int count = 0;

  if (! (cmd = mutt_buffer_new ()))
  {
    dprint (1, (debugfile, "imap_exec_msgset: unable to allocate buffer\n"));
    return -1;
  }

  /* We make a copy of the headers just in case resorting doesn't give
   exactly the original order (duplicate messages?), because other parts of
   the ctx are tied to the header order. This may be overkill. */
  oldsort = Sort;
  if (Sort != SORT_ORDER)
  {
    hdrs = idata->ctx->hdrs;
    idata->ctx->hdrs = safe_malloc (idata->ctx->msgcount * sizeof (HEADER*));
    memcpy (idata->ctx->hdrs, hdrs, idata->ctx->msgcount * sizeof (HEADER*));

    Sort = SORT_ORDER;
    qsort (idata->ctx->hdrs, idata->ctx->msgcount, sizeof (HEADER*),
           mutt_get_sort_func (SORT_ORDER));
  }

  pos = 0;

  do
  {
    cmd->dptr = cmd->data;
    mutt_buffer_printf (cmd, "%s ", pre);
    rc = imap_make_msg_set (idata, cmd, flag, changed, invert, &pos);
    if (rc > 0)
    {
      mutt_buffer_printf (cmd, " %s", post);
      if (imap_exec (idata, cmd->data, IMAP_CMD_QUEUE))
      {
        rc = -1;
        goto out;
      }
      count += rc;
    }
  }
  while (rc > 0);

  rc = count;

out:
  mutt_buffer_free (&cmd);
  if (oldsort != Sort)
  {
    Sort = oldsort;
    FREE (&idata->ctx->hdrs);
    idata->ctx->hdrs = hdrs;
  }

  return rc;
}