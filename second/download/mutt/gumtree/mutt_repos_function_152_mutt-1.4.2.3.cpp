int mutt_check_traditional_pgp (HEADER *h, int *redraw)
{
  int i;
  int rv = 0;
  if (h)
    rv = _mutt_check_traditional_pgp (h, redraw);
  else
  {
    for (i = 0; i < Context->vcount; i++)
      if (Context->hdrs[Context->v2r[i]]->tagged)
	rv = _mutt_check_traditional_pgp (Context->hdrs[Context->v2r[i]], redraw)
	  || rv;
  }
  return rv;
}