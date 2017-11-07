int imap_append_message (CONTEXT *ctx, MESSAGE *msg)
{
  IMAP_DATA* idata;
  FILE *fp;
  char buf[LONG_STRING];
  char mbox[LONG_STRING];
  char mailbox[LONG_STRING]; 
  size_t len;
  int c, last;
  IMAP_MBOX mx;
  int rc;

  idata = (IMAP_DATA*) ctx->data;

  if (imap_parse_path (ctx->path, &mx))
    return -1;

  imap_fix_path (idata, mx.mbox, mailbox, sizeof (mailbox));
  
  if ((fp = fopen (msg->path, "r")) == NULL)
  {
    mutt_perror (msg->path);
    goto fail;
  }

  /* currently we set the \Seen flag on all messages, but probably we
   * should scan the message Status header for flag info. Since we're
   * already rereading the whole file for length it isn't any more
   * expensive (it'd be nice if we had the file size passed in already
   * by the code that writes the file, but that's a lot of changes.
   * Ideally we'd have a HEADER structure with flag info here... */
  for (last = EOF, len = 0; (c = fgetc(fp)) != EOF; last = c)
  {
    if(c == '\n' && last != '\r')
      len++;

    len++;
  }
  rewind (fp);
  
  imap_munge_mbox_name (mbox, sizeof (mbox), mailbox);
  snprintf (buf, sizeof (buf), "APPEND %s (\\Seen) {%d}", mbox, len);

  imap_cmd_start (idata, buf);

  do
    rc = imap_cmd_step (idata);
  while (rc == IMAP_CMD_CONTINUE);

  if (rc != IMAP_CMD_RESPOND)
  {
    char *pc;

    dprint (1, (debugfile, "imap_append_message(): command failed: %s\n",
		idata->cmd.buf));

    pc = idata->cmd.buf + SEQLEN;
    SKIPWS (pc);
    pc = imap_next_word (pc);
    mutt_error ("%s", pc);
    mutt_sleep (1);
    fclose (fp);
    goto fail;
  }

  mutt_message _("Uploading message ...");

  for (last = EOF, len = 0; (c = fgetc(fp)) != EOF; last = c)
  {
    if (c == '\n' && last != '\r')
      buf[len++] = '\r';

    buf[len++] = c;

    if (len > sizeof(buf) - 3)
      flush_buffer(buf, &len, idata->conn);
  }
  
  if (len)
    flush_buffer(buf, &len, idata->conn);

  mutt_socket_write (idata->conn, "\r\n");
  fclose (fp);

  do
    rc = imap_cmd_step (idata);
  while (rc == IMAP_CMD_CONTINUE);

  if (!imap_code (idata->cmd.buf))
  {
    char *pc;

    dprint (1, (debugfile, "imap_append_message(): command failed: %s\n",
		idata->cmd.buf));
    pc = idata->cmd.buf + SEQLEN;
    SKIPWS (pc);
    pc = imap_next_word (pc);
    mutt_error ("%s", pc);
    mutt_sleep (1);
    goto fail;
  }

  FREE (&mx.mbox);
  return 0;

 fail:
  FREE (&mx.mbox);
  return -1;
}