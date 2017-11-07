void mutt_edit_file (const char *editor, const char *data)
{
  char cmd[LONG_STRING];
  
  mutt_endwin (NULL);
  mutt_expand_file_fmt (cmd, sizeof (cmd), editor, data);
  if (mutt_system (cmd) == -1)
    mutt_error (_("Error running \"%s\"!"), cmd);
  keypad (stdscr, TRUE);
  clearok (stdscr, TRUE);
}