static void mix_redraw_head (MIXCHAIN *chain)
{
  SETCOLOR (MT_COLOR_STATUS);
  mvprintw (MIX_VOFFSET - 1, 0, "-- Remailer chain [Length: %d]", chain ? chain->cl : 0);
  clrtoeol ();
  NORMAL_COLOR;
}