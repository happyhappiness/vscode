static void start_curses (void)
{
  km_init (); /* must come before mutt_init */

#ifdef USE_SLANG_CURSES
  SLtt_Ignore_Beep = 1; /* don't do that #*$@^! annoying visual beep! */
  SLsmg_Display_Eight_Bit = 128; /* characters above this are printable */
  SLtt_set_color(0, NULL, "default", "default");
#if SLANG_VERSION >= 20000
  SLutf8_enable(-1);
#endif
#else
  /* should come before initscr() so that ncurses 4.2 doesn't try to install
     its own SIGWINCH handler */
  mutt_signal_init ();
#endif
  if (initscr () == NULL)
  {
    puts _("Error initializing terminal.");
    exit (1);
  }
#if 1 /* USE_SLANG_CURSES  - commenting out suggested in #455. */
  /* slang requires the signal handlers to be set after initializing */
  mutt_signal_init ();
#endif
  ci_start_color ();
  keypad (stdscr, TRUE);
  cbreak ();
  noecho ();
#if HAVE_TYPEAHEAD
  typeahead (-1);       /* simulate smooth scrolling */
#endif
#if HAVE_META
  meta (stdscr, TRUE);
#endif
init_extended_keys();
  mutt_reflow_windows ();
}