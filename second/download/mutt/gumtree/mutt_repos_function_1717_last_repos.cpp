static int ci_first_message (void)
{
  int old = -1, i;

  if (Context && Context->msgcount)
  {
    for (i=0; i < Context->vcount; i++)
    {
      if (! Context->hdrs[Context->v2r[i]]->read &&
	  ! Context->hdrs[Context->v2r[i]]->deleted)
      {
	if (! Context->hdrs[Context->v2r[i]]->old)
	  return (i);
	else if (old == -1)
	  old = i;
      }
    }
    if (old != -1)
      return (old);

    /* If Sort is reverse and not threaded, the latest message is first.
     * If Sort is threaded, the latest message is first iff exactly one
     * of Sort and SortAux are reverse.
     */
    if (((Sort & SORT_REVERSE) && (Sort & SORT_MASK) != SORT_THREADS) ||
	((Sort & SORT_MASK) == SORT_THREADS &&
	 ((Sort ^ SortAux) & SORT_REVERSE)))
      return 0;
    else
      return (Context->vcount ? Context->vcount - 1 : 0);
  }
  return 0;
}