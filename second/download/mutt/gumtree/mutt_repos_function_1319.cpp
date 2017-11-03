void menu_redraw_sidebar (MUTTMENU *menu)
{
  SidebarNeedsRedraw = 0;
  mutt_sb_draw ();
}