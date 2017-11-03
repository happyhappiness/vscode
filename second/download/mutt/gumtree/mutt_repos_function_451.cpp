void mutt_refresh (void)
{
  /* don't refresh when we are waiting for a child. */
  if (option (OPTKEEPQUIET))
    return;

  /* don't refresh in the middle of macros unless necessary */
  if (UngetCount && !option (OPTFORCEREFRESH))
    return;

  /* else */
  refresh ();
}