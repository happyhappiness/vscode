static void redraw_mix_line (LIST *chain)
{
  int c;
  char *t;

  mvaddstr (HDR_MIX, 0,     "     Mix: ");

  if (!chain)
  {
    addstr ("<no chain defined>");
    clrtoeol ();
    return;
  }
  
  for (c = 12; chain; chain = chain->next)
  {
    t = chain->data;
    if (t && t[0] == '0' && t[1] == '\0')
      t = "<random>";
    
    if (c + mutt_strlen (t) + 2 >= COLS)
      break;

    addstr (NONULL(t));
    if (chain->next)
      addstr (", ");

    c += mutt_strlen (t) + 2;
  }
}