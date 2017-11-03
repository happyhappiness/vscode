static int delete_attachment (MUTTMENU *menu, short *idxlen, int x)
{
  ATTACHPTR **idx = (ATTACHPTR **) menu->data;
  int y;

  menu->redraw = REDRAW_INDEX | REDRAW_STATUS;

  if (x == 0 && menu->max == 1)
  {
    mutt_error _("You may not delete the only attachment.");
    idx[x]->content->tagged = 0;
    return (-1);
  }

  for (y = 0; y < *idxlen; y++)
  {
    if (idx[y]->content->next == idx[x]->content)
    {
      idx[y]->content->next = idx[x]->content->next;
      break;
    }
  }

  idx[x]->content->next = NULL;
  idx[x]->content->parts = NULL;
  mutt_free_body (&(idx[x]->content));
  FREE (&idx[x]->tree);
  FREE (&idx[x]);
  for (; x < *idxlen - 1; x++)
    idx[x] = idx[x+1];
  idx[*idxlen - 1] = NULL;
  menu->max = --(*idxlen);
  
  return (0);
}