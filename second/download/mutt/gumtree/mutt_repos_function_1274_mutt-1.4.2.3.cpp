int imap_cmd_start (IMAP_DATA* idata, const char* cmd)
{
  char* out;
  int outlen;
  int rc;

  if (idata->status == IMAP_FATAL)
  {
    cmd_handle_fatal (idata);
    return IMAP_CMD_BAD;
  }

  cmd_make_sequence (idata);
  /* seq, space, cmd, \r\n\0 */
  outlen = strlen (idata->cmd.seq) + strlen (cmd) + 4;
  out = (char*) safe_malloc (outlen);
  snprintf (out, outlen, "%s %s\r\n", idata->cmd.seq, cmd);

  rc = mutt_socket_write (idata->conn, out);

  FREE (&out);

  return (rc < 0) ? IMAP_CMD_BAD : 0;
}