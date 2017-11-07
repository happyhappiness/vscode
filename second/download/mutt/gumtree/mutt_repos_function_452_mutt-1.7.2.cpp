void mutt_need_hard_redraw (void)
{
  keypad (stdscr, TRUE);
  clearok (stdscr, TRUE);
  set_option (OPTNEEDREDRAW);
}