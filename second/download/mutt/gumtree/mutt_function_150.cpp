static void mix_redraw_head (MIXCHAIN *chain)
{
  SETCOLOR (MT_COLOR_STATUS);
  mutt_window_mvprintw (MuttIndexWindow, MIX_VOFFSET - 1, 0,
                        "-- Remailer chain [Length: %d]", chain ? chain->cl : 0);
  mutt_window_clrtoeol (MuttIndexWindow);
  NORMAL_COLOR;
}