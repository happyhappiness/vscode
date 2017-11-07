void mutt_edit_file (const char *editor, const char *data)
{
  char cmd[LONG_STRING];
  
  mutt_endwin (NULL);
  mutt_expand_file_fmt (cmd, sizeof (cmd), editor, data);
  if (mutt_system (cmd))
  {
    mutt_error (_("Error running \"%s\"!"), cmd);
    mutt_sleep (2);
  }
#if defined (USE_SLANG_CURSES) || defined (HAVE_RESIZETERM)
  /* the terminal may have been resized while the editor owned it */
  mutt_resize_screen ();
#endif
  keypad (stdscr, TRUE);
  clearok (stdscr, TRUE);
}