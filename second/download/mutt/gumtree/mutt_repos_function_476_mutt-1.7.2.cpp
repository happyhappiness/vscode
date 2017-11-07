void mutt_show_error (void)
{
  if (option (OPTKEEPQUIET))
    return;
  
  SETCOLOR (option (OPTMSGERR) ? MT_COLOR_ERROR : MT_COLOR_MESSAGE);
  mutt_window_mvaddstr (MuttMessageWindow, 0, 0, Errorbuf);
  NORMAL_COLOR;
  mutt_window_clrtoeol(MuttMessageWindow);
}