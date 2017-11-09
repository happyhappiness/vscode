static void
expand_command_str (const CONTEXT *ctx, const char *cmd, char *buf, int buflen)
{
  if (!ctx || !cmd || !buf)
    return;

  mutt_FormatString (buf, buflen, 0, buflen, cmd, cb_format_str, (unsigned long) ctx, 0);
}