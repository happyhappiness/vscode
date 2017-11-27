void cmd_destroy(cmd_t *cmd) {
  if (cmd == NULL)
    return;

  switch (cmd->type) {
  case CMD_UNKNOWN:
    /* nothing to do */
    break;
  case CMD_FLUSH:
    cmd_destroy_flush(&cmd->cmd.flush);
    break;
  case CMD_GETVAL:
    cmd_destroy_getval(&cmd->cmd.getval);
    break;
  case CMD_LISTVAL:
    cmd_destroy_listval(&cmd->cmd.listval);
    break;
  case CMD_PUTVAL:
    cmd_destroy_putval(&cmd->cmd.putval);
    break;
  }
}