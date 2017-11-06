void mutt_resize_screen (void)
{
  char *cp;
  int fd;
  struct winsize w;
#ifdef HAVE_RESIZETERM
  int SLtt_Screen_Rows, SLtt_Screen_Cols;
#endif

  SLtt_Screen_Rows = -1;
  SLtt_Screen_Cols = -1;
  if ((fd = open ("/dev/tty", O_RDONLY)) != -1)
  {
    if (ioctl (fd, TIOCGWINSZ, &w) != -1)
    {
      SLtt_Screen_Rows = w.ws_row;
      SLtt_Screen_Cols = w.ws_col;
    }
    close (fd);
  }
  if (SLtt_Screen_Rows <= 0)
  {
    if ((cp = getenv ("LINES")) != NULL && mutt_atoi (cp, &SLtt_Screen_Rows) < 0)
      SLtt_Screen_Rows = 24;
  }
  if (SLtt_Screen_Cols <= 0)
  {
    if ((cp = getenv ("COLUMNS")) != NULL && mutt_atoi (cp, &SLtt_Screen_Cols) < 0)
      SLtt_Screen_Cols = 80;
  }
#ifdef USE_SLANG_CURSES
  delwin (stdscr);
  SLsmg_reset_smg ();
  SLsmg_init_smg ();
  stdscr = newwin (0, 0, 0, 0);
  keypad (stdscr, TRUE);
#else
  resizeterm (SLtt_Screen_Rows, SLtt_Screen_Cols);
#endif
  mutt_reflow_windows ();
}