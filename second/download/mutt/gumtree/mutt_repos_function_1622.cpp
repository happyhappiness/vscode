short mutt_ts_capability(void)
{
  char *term = getenv("TERM");
  char *tcaps;
  int tcapi;
  char **termp;
  char *known[] = {
    "color-xterm",
    "cygwin",
    "eterm",
    "kterm",
    "nxterm",
    "putty",
    "rxvt",
    "screen",
    "xterm",
    NULL
  };

  /* If tsl is set, then terminfo says that status lines work. */
  tcaps = tigetstr("tsl");
  if (tcaps && tcaps != (char *)-1 && *tcaps)
  {
    /* update the static defns of tsl/fsl from terminfo */
    tsl = safe_strdup(tcaps);

    tcaps = tigetstr("fsl");
    if (tcaps && tcaps != (char *)-1 && *tcaps)
      fsl = safe_strdup(tcaps);

    return 1;
  }

  /* If XT (boolean) is set, then this terminal supports the standard escape. */
  /* Beware: tigetflag returns -1 if XT is invalid or not a boolean. */
#ifdef HAVE_USE_EXTENDED_NAMES
  use_extended_names (TRUE);
  tcapi = tigetflag("XT");
  if (tcapi == 1)
    return 1;
#endif /* HAVE_USE_EXTENDED_NAMES */

  /* Check term types that are known to support the standard escape without
   * necessarily asserting it in terminfo. */
  for (termp = known; termp; termp++)
  {
    if (term && *termp && mutt_strncasecmp (term, *termp, strlen(*termp)))
      return 1;
  }

  /* not supported */
  return 0;
}