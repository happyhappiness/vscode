int imap_exec (IMAP_DATA* idata, const char* cmd, int flags)
{
  char* out;
  int outlen;
  int rc;

  if (idata->status == IMAP_FATAL)
  {
    cmd_handle_fatal (idata);
    return -1;
  }

  /* create sequence for command */
  cmd_make_sequence (idata);
  /* seq, space, cmd, \r\n\0 */
  outlen = strlen (idata->cmd.seq) + strlen (cmd) + 4;
  out = (char*) safe_malloc (outlen);
  snprintf (out, outlen, "%s %s\r\n", idata->cmd.seq, cmd);

  rc = mutt_socket_write_d (idata->conn, out,
    flags & IMAP_CMD_PASS ? IMAP_LOG_PASS : IMAP_LOG_CMD);
  safe_free ((void**) &out);

  if (rc < 0)
  {
    cmd_handle_fatal (idata);
    return -1;
  }

  do
    rc = imap_cmd_step (idata);
  while (rc == IMAP_CMD_CONTINUE);

  if (rc == IMAP_CMD_NO && (flags & IMAP_CMD_FAIL_OK))
    return -2;

  if (rc != IMAP_CMD_OK)
  {
    if (flags & IMAP_CMD_FAIL_OK)
      return -2;

    dprint (1, (debugfile, "imap_exec: command failed: %s\n", idata->cmd.buf));
    return -1;
  }

  return 0;
}