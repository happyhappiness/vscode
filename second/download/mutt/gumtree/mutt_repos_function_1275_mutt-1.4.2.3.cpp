int imap_cmd_step (IMAP_DATA* idata)
{
  IMAP_COMMAND* cmd = &idata->cmd;
  unsigned int len = 0;
  int c;

  if (idata->status == IMAP_FATAL)
  {
    cmd_handle_fatal (idata);
    return IMAP_CMD_BAD;
  }

  /* read into buffer, expanding buffer as necessary until we have a full
   * line */
  do
  {
    if (len == cmd->blen)
    {
      safe_realloc ((void**) &cmd->buf, cmd->blen + IMAP_CMD_BUFSIZE);
      cmd->blen = cmd->blen + IMAP_CMD_BUFSIZE;
      dprint (3, (debugfile, "imap_cmd_step: grew buffer to %u bytes\n",
		  cmd->blen));
    }

    c = mutt_socket_readln (cmd->buf + len, cmd->blen - len, idata->conn);
    if (c <= 0)
    {
      dprint (1, (debugfile, "imap_cmd_step: Error reading server response.\n"));
      cmd_handle_fatal (idata);
      return IMAP_CMD_BAD;
    }

    len += c;
  }
  /* if we've read all the way to the end of the buffer, we haven't read a
   * full line (mutt_socket_readln strips the \r, so we always have at least
   * one character free when we've read a full line) */
  while (len == cmd->blen);

  /* don't let one large string make cmd->buf hog memory forever */
  if ((cmd->blen > IMAP_CMD_BUFSIZE) && (len <= IMAP_CMD_BUFSIZE))
  {
    safe_realloc ((void**) &cmd->buf, IMAP_CMD_BUFSIZE);
    cmd->blen = IMAP_CMD_BUFSIZE;
    dprint (3, (debugfile, "imap_cmd_step: shrank buffer to %u bytes\n", cmd->blen));
  }
  
  /* handle untagged messages. The caller still gets its shot afterwards. */
  if (!ascii_strncmp (cmd->buf, "* ", 2) &&
      cmd_handle_untagged (idata))
    return IMAP_CMD_BAD;

  /* server demands a continuation response from us */
  if (!ascii_strncmp (cmd->buf, "+ ", 2))
  {
    return IMAP_CMD_RESPOND;
  }

  /* tagged completion code */
  if (!ascii_strncmp (cmd->buf, cmd->seq, SEQLEN))
  {
    imap_cmd_finish (idata);
    return imap_code (cmd->buf) ? IMAP_CMD_OK : IMAP_CMD_NO;
  }

  return IMAP_CMD_CONTINUE;
}