IMAP_DATA* imap_new_idata (void) {
  IMAP_DATA* idata;

  idata = safe_calloc (1, sizeof (IMAP_DATA));
  if (!idata)
    return NULL;

  idata->conn = NULL;
  idata->capstr = NULL;
  idata->state = IMAP_DISCONNECTED;
  idata->seqno = 0;

  idata->cmd.buf = NULL;
  idata->cmd.blen = 0;
  idata->cmd.state = IMAP_CMD_OK;

  return idata;
}