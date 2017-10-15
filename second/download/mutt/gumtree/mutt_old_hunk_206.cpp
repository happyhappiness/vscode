  /* icon setting is not supported in terminfo, so hardcode the escape - yuck */
  fprintf(stderr, "\033]1;%s\007", str);
}

void index_make_entry (char *s, size_t l, MUTTMENU *menu, int num)
{
  format_flag flag = M_FORMAT_MAKEPRINT | M_FORMAT_ARROWCURSOR | M_FORMAT_INDEX;
  int edgemsgno, reverse = Sort & SORT_REVERSE;
  HEADER *h = Context->hdrs[Context->v2r[num]];
  THREAD *tmp;

  if ((Sort & SORT_MASK) == SORT_THREADS && h->tree)
  {
    flag |= M_FORMAT_TREE; /* display the thread tree */
    if (h->display_subject)
      flag |= M_FORMAT_FORCESUBJ;
    else
    {
      if (reverse)
      {
	if (menu->top + menu->pagelen > menu->max)
	  edgemsgno = Context->v2r[menu->max - 1];
