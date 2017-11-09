static void index_menu_redraw (MUTTMENU *menu)
{
  char buf[LONG_STRING];

  if (menu->redraw & REDRAW_FULL)
  {
    menu_redraw_full (menu);
    mutt_show_error ();
  }

#ifdef USE_SIDEBAR
  if (menu->redraw & REDRAW_SIDEBAR)
  {
    mutt_sb_set_buffystats (Context);
    menu_redraw_sidebar (menu);
  }
#endif

  if (Context && Context->hdrs && !(menu->current >= Context->vcount))
  {
    menu_check_recenter (menu);

    if (menu->redraw & REDRAW_INDEX)
    {
      menu_redraw_index (menu);
      menu->redraw |= REDRAW_STATUS;
    }
    else if (menu->redraw & (REDRAW_MOTION_RESYNCH | REDRAW_MOTION))
      menu_redraw_motion (menu);
    else if (menu->redraw & REDRAW_CURRENT)
      menu_redraw_current (menu);
  }

  if (menu->redraw & REDRAW_STATUS)
  {
    menu_status_line (buf, sizeof (buf), menu, NONULL (Status));
    mutt_window_move (MuttStatusWindow, 0, 0);
    SETCOLOR (MT_COLOR_STATUS);
    mutt_paddstr (MuttStatusWindow->cols, buf);
    NORMAL_COLOR;
    menu->redraw &= ~REDRAW_STATUS;
    if (option(OPTTSENABLED) && TSSupported)
    {
      menu_status_line (buf, sizeof (buf), menu, NONULL (TSStatusFormat));
      mutt_ts_status(buf);
      menu_status_line (buf, sizeof (buf), menu, NONULL (TSIconFormat));
      mutt_ts_icon(buf);
    }
  }

  menu->redraw = 0;
}