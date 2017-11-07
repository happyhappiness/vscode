static void mix_redraw_chain (REMAILER **type2_list,
			      struct coord *coords,
			      MIXCHAIN *chain,
			      int cur)
{
  int i;
  
  for (i = MIX_VOFFSET; i < MIX_MAXROW; i++)
  {
    move (i, 0);
    clrtoeol ();
  }

  for (i = 0; i < chain->cl; i++)
    mix_redraw_ce (type2_list, coords, chain, i, i == cur);
}