static void mix_redraw_chain (REMAILER **type2_list,
			      struct coord *coords,
			      MIXCHAIN *chain,
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