int menu_redraw (MUTTMENU *menu)
{
  /* See if all or part of the screen needs to be updated.  */
  if (menu->redraw & REDRAW_FULL)
  {
    menu_redraw_full (menu);
    /* allow the caller to do any local configuration */
    return (OP_REDRAW);
  }
  
  if (!menu->dialog)
    menu_check_recenter (menu);
  
  if (menu->redraw & REDRAW_STATUS)
    menu_redraw_status (menu);
#ifdef USE_SIDEBAR
  if (menu->redraw & REDRAW_SIDEBAR || SidebarNeedsRedraw)
    menu_redraw_sidebar (menu);
#endif
  if (menu->redraw & REDRAW_INDEX)
    menu_redraw_index (menu);
  else if (menu->redraw & (REDRAW_MOTION | REDRAW_MOTION_RESYNCH))
    menu_redraw_motion (menu);
  else if (menu->redraw == REDRAW_CURRENT)
    menu_redraw_current (menu);
  
  if (menu->dialog)
    menu_redraw_prompt (menu);
  
  return OP_NULL;
}