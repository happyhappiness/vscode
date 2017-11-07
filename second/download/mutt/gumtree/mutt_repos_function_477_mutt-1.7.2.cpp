void mutt_endwin (const char *msg)
{
  int e = errno;

  if (!option (OPTNOCURSES))
  {
    /* at least in some situations (screen + xterm under SuSE11/12) endwin()
     * doesn't properly flush the screen without an explicit call.
     */
    mutt_refresh();
    endwin ();
  }
  
  if (msg && *msg)
  {
    puts (msg);
    fflush (stdout);
  }

  errno = e;
}