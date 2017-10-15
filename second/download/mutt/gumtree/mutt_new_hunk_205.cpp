
out:
  if (pos >= progress->size)
    mutt_clear_error ();
}

void mutt_init_windows ()
{
  MuttHelpWindow = safe_calloc (sizeof (mutt_window_t), 1);
  MuttIndexWindow = safe_calloc (sizeof (mutt_window_t), 1);
  MuttStatusWindow = safe_calloc (sizeof (mutt_window_t), 1);
  MuttMessageWindow = safe_calloc (sizeof (mutt_window_t), 1);
#ifdef USE_SIDEBAR
  MuttSidebarWindow = safe_calloc (sizeof (mutt_window_t), 1);
#endif
}

void mutt_free_windows ()
{
  FREE (&MuttHelpWindow);
  FREE (&MuttIndexWindow);
  FREE (&MuttStatusWindow);
  FREE (&MuttMessageWindow);
#ifdef USE_SIDEBAR
  FREE (&MuttSidebarWindow);
#endif
}

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

int mutt_window_move (mutt_window_t *win, int row, int col)
{
  return move (win->row_offset + row, win->col_offset + col);
}

int mutt_window_mvaddch (mutt_window_t *win, int row, int col, const chtype ch)
{
  return mvaddch (win->row_offset + row, win->col_offset + col, ch);
}

int mutt_window_mvaddstr (mutt_window_t *win, int row, int col, const char *str)
{
  return mvaddstr (win->row_offset + row, win->col_offset + col, str);
}

#ifdef USE_SLANG_CURSES
static int vw_printw (SLcurses_Window_Type *win, const char *fmt, va_list ap)
{
  char buf[LONG_STRING];

  (void) SLvsnprintf (buf, sizeof (buf), (char *)fmt, ap);
  SLcurses_waddnstr (win, buf, -1);
  return 0;
}
#endif

int mutt_window_mvprintw (mutt_window_t *win, int row, int col, const char *fmt, ...)
{
  va_list ap;
  int rv;

  if ((rv = mutt_window_move (win, row, col) != ERR))
  {
    va_start (ap, fmt);
    rv = vw_printw (stdscr, fmt, ap);
    va_end (ap);
  }

  return rv;
}

/* Assumes the cursor has already been positioned within the
 * window.
 */
void mutt_window_clrtoeol (mutt_window_t *win)
{
  int row, col, curcol;

  if (win->col_offset + win->cols == COLS)
    clrtoeol ();
  else
  {
    getyx (stdscr, row, col);
    curcol = col;
    while (curcol < win->col_offset + win->cols)
    {
      addch (' ');
      curcol++;
    }
    move (row, col);
  }
}

void mutt_window_clearline (mutt_window_t *win, int row)
{
  mutt_window_move (win, row, 0);
  mutt_window_clrtoeol (win);
}

/* Assumes the current position is inside the window.
 * Otherwise it will happily return negative or values outside
 * the window boundaries
 */
void mutt_window_getyx (mutt_window_t *win, int *y, int *x)
{
  int row, col;

  getyx (stdscr, row, col);
  if (y)
    *y = row - win->row_offset;
  if (x)
    *x = col - win->col_offset;
}


void mutt_show_error (void)
{
  if (option (OPTKEEPQUIET))
    return;
  
  SETCOLOR (option (OPTMSGERR) ? MT_COLOR_ERROR : MT_COLOR_MESSAGE);
  mutt_window_mvaddstr (MuttMessageWindow, 0, 0, Errorbuf);
  NORMAL_COLOR;
  mutt_window_clrtoeol(MuttMessageWindow);
}

void mutt_endwin (const char *msg)
{
  int e = errno;

