int imap_cmd_idle (IMAP_DATA* idata)
{
  int rc;

  imap_cmd_start (idata, "IDLE");
  do
    rc = imap_cmd_step (idata);
  while (rc == IMAP_CMD_CONTINUE);

  if (rc == IMAP_CMD_RESPOND)
  {
    /* successfully entered IDLE state */
    idata->state = IMAP_IDLE;
    /* queue automatic exit when next command is issued */
    mutt_buffer_printf (idata->cmdbuf, "DONE\r\n");
    rc = IMAP_CMD_OK;
  }
  if (rc != IMAP_CMD_OK)
  {
    dprint (1, (debugfile, "imap_cmd_idle: error starting IDLE\n"));
    return -1;
  }
  
  return 0;
}