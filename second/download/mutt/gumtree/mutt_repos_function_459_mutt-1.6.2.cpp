void mutt_show_error (void)
{
  if (option (OPTKEEPQUIET))
    return;
  
  SETCOLOR (option (OPTMSGERR) ? MT_COLOR_ERROR : MT_COLOR_MESSAGE);
  mvaddstr(LINES-1, 0, Errorbuf);
  NORMAL_COLOR;
  clrtoeol();
}