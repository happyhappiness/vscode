void mutt_current_menu_redraw ()
{
  MUTTMENU *current_menu;

  current_menu = get_current_menu ();
  if (current_menu)
  {
    if (menu_redraw (current_menu) == OP_REDRAW)
    /* On a REDRAW_FULL with a non-customized redraw, menu_redraw()
     * will return OP_REDRAW to give the calling menu-loop a chance to
     * customize output.
     */
       menu_redraw (current_menu);
  }
}