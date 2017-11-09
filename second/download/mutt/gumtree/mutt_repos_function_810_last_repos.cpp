static void redraw_mix_line (LIST *chain)
{
  int c;
  char *t;

  SETCOLOR (MT_COLOR_COMPOSE_HEADER);
  mutt_window_mvprintw (MuttIndexWindow, HDR_MIX, 0,
                        "%*s", HeaderPadding[HDR_MIX], _(Prompts[HDR_MIX]));
  NORMAL_COLOR;

  if (!chain)
  {
    addstr ("<no chain defined>");
    mutt_window_clrtoeol (MuttIndexWindow);
    return;
  }
  
  for (c = 12; chain; chain = chain->next)
  {
    t = chain->data;
    if (t && t[0] == '0' && t[1] == '\0')
      t = "<random>";
    
    if (c + mutt_strlen (t) + 2 >= MuttIndexWindow->cols)
      break;

    addstr (NONULL(t));
    if (chain->next)
      addstr (", ");

    c += mutt_strlen (t) + 2;
  }
}