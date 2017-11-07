static void resort_index (MUTTMENU *menu)
{
  int i;
  HEADER *current = CURHDR;

  menu->current = -1;
  mutt_sort_headers (Context, 0);
  /* Restore the current message */

  for (i = 0; i < Context->vcount; i++)
  {
    if (Context->hdrs[Context->v2r[i]] == current)
    {
      menu->current = i;
      break;
    }
  }

  if ((Sort & SORT_MASK) == SORT_THREADS && menu->current < 0)
    menu->current = mutt_parent_message (Context, current);

  if (menu->current < 0)
    menu->current = ci_first_message ();

  menu->redraw = REDRAW_INDEX | REDRAW_STATUS;
}