static void mix_redraw_ce (REMAILER **type2_list,
			   struct coord *coords,
			   MIXCHAIN *chain,
			   int i,
			   short selected)
{
  if (!coords || !chain)
    return;
  
  if (coords[i].r < MIX_MAXROW)
  {
    
    if (selected)
      SETCOLOR (MT_COLOR_INDICATOR);
    else
      NORMAL_COLOR;
    
    mutt_window_mvaddstr (MuttIndexWindow, coords[i].r, coords[i].c,
                          type2_list[chain->ch[i]]->shortname);
    NORMAL_COLOR;

    if (i + 1 < chain->cl)
      addstr (", ");
  }
}