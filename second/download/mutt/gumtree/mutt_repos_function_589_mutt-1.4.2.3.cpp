static void mix_redraw_head (MIXCHAIN *chain)
{
  SETCOLOR (MT_COLOR_STATUS);
  mvprintw (MIX_VOFFSET - 1, 0, "-- Remailer chain [Length: %d]", chain ? chain->cl : 0);
  
  BKGDSET (MT_COLOR_STATUS);
  clrtoeol ();
  
  BKGDSET (MT_COLOR_NORMAL);
  SETCOLOR (MT_COLOR_NORMAL);
}