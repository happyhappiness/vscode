int
mutt_comp_valid_command (const char *cmd)
{
  if (!cmd)
    return 0;

  return (strstr (cmd, "%f") && strstr (cmd, "%t"));
}