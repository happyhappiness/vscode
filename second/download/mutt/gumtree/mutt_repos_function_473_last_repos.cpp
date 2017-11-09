static void reflow_message_window_rows (int mw_rows)
{
  MuttMessageWindow->rows = mw_rows;
  MuttMessageWindow->row_offset = LINES - mw_rows;

  MuttStatusWindow->row_offset = option (OPTSTATUSONTOP) ? 0 : LINES - mw_rows - 1;

  if (option (OPTHELP))
    MuttHelpWindow->row_offset = option (OPTSTATUSONTOP) ? LINES - mw_rows - 1 : 0;

  MuttIndexWindow->rows = MAX(LINES - MuttStatusWindow->rows -
			      MuttHelpWindow->rows - MuttMessageWindow->rows, 0);

#ifdef USE_SIDEBAR
  if (option (OPTSIDEBAR))
    MuttSidebarWindow->rows = MuttIndexWindow->rows;
#endif

  /* We don't also set REDRAW_FLOW because this function only
   * changes rows and is a temporary adjustment. */
  mutt_set_current_menu_redraw_full ();
}