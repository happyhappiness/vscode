int imap_cmd_running (IMAP_DATA* idata)
{
  if (idata->cmd.state == IMAP_CMD_CONTINUE ||
      idata->cmd.state == IMAP_CMD_RESPOND)
    return 1;

  return 0;
}