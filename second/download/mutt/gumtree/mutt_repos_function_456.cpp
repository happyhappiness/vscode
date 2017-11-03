void mutt_clear_error (void)
{
  Errorbuf[0] = 0;
  if (!option(OPTNOCURSES))
    mutt_window_clearline (MuttMessageWindow, 0);
}