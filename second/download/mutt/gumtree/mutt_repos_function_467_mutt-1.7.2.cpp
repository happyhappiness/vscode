void mutt_reflow_windows (void)
{
  if (option (OPTNOCURSES))
    return;

  dprint (2, (debugfile, "In mutt_reflow_windows\n"));

  MuttStatusWindow->rows = 1;
  MuttStatusWindow->cols = COLS;
  MuttStatusWindow->row_offset = option (OPTSTATUSONTOP) ? 0 : LINES - 2;
  MuttStatusWindow->col_offset = 0;

  memcpy (MuttHelpWindow, MuttStatusWindow, sizeof (mutt_window_t));
  if (! option (OPTHELP))
    MuttHelpWindow->rows = 0;
  else
    MuttHelpWindow->row_offset = option (OPTSTATUSONTOP) ? LINES - 2 : 0;

  memcpy (MuttMessageWindow, MuttStatusWindow, sizeof (mutt_window_t));
  MuttMessageWindow->row_offset = LINES - 1;

  memcpy (MuttIndexWindow, MuttStatusWindow, sizeof (mutt_window_t));
  MuttIndexWindow->rows = MAX(LINES - MuttStatusWindow->rows -
			      MuttHelpWindow->rows - MuttMessageWindow->rows, 0);
  MuttIndexWindow->row_offset = option (OPTSTATUSONTOP) ? MuttStatusWindow->rows :
                                                          MuttHelpWindow->rows;

#ifdef USE_SIDEBAR
  if (option (OPTSIDEBAR))
  {
    memcpy (MuttSidebarWindow, MuttIndexWindow, sizeof (mutt_window_t));
    MuttSidebarWindow->cols = SidebarWidth;

    MuttIndexWindow->cols -= SidebarWidth;
    MuttIndexWindow->col_offset += SidebarWidth;
  }
#endif
}