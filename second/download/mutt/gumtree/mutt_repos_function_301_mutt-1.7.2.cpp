int pgp_use_gpg_agent (void)
{
  char *tty;

  /* GnuPG 2.1 no longer exports GPG_AGENT_INFO */
  if (!option (OPTUSEGPGAGENT))
    return 0;

  if ((tty = ttyname(0)))
    setenv("GPG_TTY", tty, 0);

  return 1;
}