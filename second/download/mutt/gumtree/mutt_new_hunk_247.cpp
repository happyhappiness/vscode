			      int cur)
{
  int i;
  
  for (i = MIX_VOFFSET; i < MIX_MAXROW; i++)
  {
    mutt_window_move (MuttIndexWindow, i, 0);
    mutt_window_clrtoeol (MuttIndexWindow);
  }

  for (i = 0; i < chain->cl; i++)
    mix_redraw_ce (type2_list, coords, chain, i, i == cur);
}

static void mix_redraw_head (MIXCHAIN *chain)
{
  SETCOLOR (MT_COLOR_STATUS);
  mutt_window_mvprintw (MuttIndexWindow, MIX_VOFFSET - 1, 0,
                        "-- Remailer chain [Length: %d]", chain ? chain->cl : 0);
  mutt_window_clrtoeol (MuttIndexWindow);
  NORMAL_COLOR;
}

static const char *mix_format_caps (REMAILER *r)
{
  static char capbuff[10];
