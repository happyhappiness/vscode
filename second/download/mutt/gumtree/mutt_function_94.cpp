int mutt_write_one_header (FILE *fp, const char *tag, const char *value,
			   const char *pfx, int wraplen, int flags)
{
  char *p = (char *)value, *last, *line;
  int max = 0, w, rc = -1;
  int pfxw = mutt_strwidth (pfx);
  char *v = safe_strdup (value);

  if (!(flags & CH_DISPLAY) || option (OPTWEED))
    v = unfold_header (v);

  /* when not displaying, use sane wrap value */
  if (!(flags & CH_DISPLAY))
  {
    if (WrapHeaders < 78 || WrapHeaders > 998)
      wraplen = 78;
    else
      wraplen = WrapHeaders;
  }
  else if (wraplen <= 0 || wraplen > COLS)
    wraplen = COLS;

  if (tag)
  {
    /* if header is short enough, simply print it */
    if (!(flags & CH_DISPLAY) && mutt_strwidth (tag) + 2 + pfxw +
	mutt_strwidth (v) <= wraplen)
    {
      dprint(4,(debugfile,"mwoh: buf[%s%s: %s] is short enough\n",
		NONULL(pfx), tag, v));
      if (fprintf (fp, "%s%s: %s\n", NONULL(pfx), tag, v) <= 0)
	goto out;
      rc = 0;
      goto out;
    }
    else
    {
      rc = fold_one_header (fp, tag, v, pfx, wraplen, flags);
      goto out;
    }
  }

  p = last = line = (char *)v;
  while (p && *p)
  {
    p = strchr (p, '\n');

    /* find maximum line width in current header */
    if (p)
      *p = 0;
    if ((w = my_width (line, 0, flags)) > max)
      max = w;
    if (p)
      *p = '\n';

    if (!p)
      break;

    line = ++p;
    if (*p != ' ' && *p != '\t')
    {
      if (write_one_header (fp, pfxw, max, wraplen, pfx, last, p, flags) < 0)
	goto out;
      last = p;
      max = 0;
    }
  }

  if (last && *last)
    if (write_one_header (fp, pfxw, max, wraplen, pfx, last, p, flags) < 0)
      goto out;

  rc = 0;

out:
  FREE (&v);
  return rc;
}