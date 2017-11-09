static int
execute_command (CONTEXT *ctx, const char *command, const char *progress)
{
  int rc = 1;
  char sys_cmd[HUGE_STRING];

  if (!ctx || !command || !progress)
    return 0;

  if (!ctx->quiet)
    mutt_message (progress, ctx->realpath);

  mutt_block_signals();
  endwin();
  fflush (stdout);

  expand_command_str (ctx, command, sys_cmd, sizeof (sys_cmd));

  if (mutt_system (sys_cmd) != 0)
  {
    rc = 0;
    mutt_any_key_to_continue (NULL);
    mutt_error (_("Error running \"%s\"!"), sys_cmd);
  }

  mutt_unblock_signals();

  return rc;
}