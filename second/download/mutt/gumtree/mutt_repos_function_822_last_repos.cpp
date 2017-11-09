static void compose_menu_redraw (MUTTMENU *menu)
{
  char buf[LONG_STRING];
  compose_redraw_data_t *rd = menu->redraw_data;

  if (!rd)
    return;

  if (menu->redraw & REDRAW_FULL)
  {
    menu_redraw_full (menu);

    draw_envelope (rd->msg, rd->fcc);
    menu->offset = HDR_ATTACH;
    menu->pagelen = MuttIndexWindow->rows - HDR_ATTACH;
  }

  menu_check_recenter (menu);

  if (menu->redraw & REDRAW_STATUS)
  {
    compose_status_line (buf, sizeof (buf), 0, MuttStatusWindow->cols, menu, NONULL(ComposeFormat));
    mutt_window_move (MuttStatusWindow, 0, 0);
    SETCOLOR (MT_COLOR_STATUS);
    mutt_paddstr (MuttStatusWindow->cols, buf);
    NORMAL_COLOR;
    menu->redraw &= ~REDRAW_STATUS;
  }

#ifdef USE_SIDEBAR
  if (menu->redraw & REDRAW_SIDEBAR)
    menu_redraw_sidebar (menu);
#endif

  if (menu->redraw & REDRAW_INDEX)
    menu_redraw_index (menu);
  else if (menu->redraw & (REDRAW_MOTION | REDRAW_MOTION_RESYNCH))
    menu_redraw_motion (menu);
  else if (menu->redraw == REDRAW_CURRENT)
    menu_redraw_current (menu);
}