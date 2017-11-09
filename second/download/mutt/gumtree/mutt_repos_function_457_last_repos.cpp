void mutt_need_hard_redraw (void)
{
  keypad (stdscr, TRUE);
  clearok (stdscr, TRUE);
  mutt_set_current_menu_redraw_full ();
}