void menu_redraw_sidebar (MUTTMENU *menu)
{
  menu->redraw &= ~REDRAW_SIDEBAR;
  mutt_sb_draw ();
}