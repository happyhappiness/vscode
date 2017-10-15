static int write_one_header (FILE *fp, int pfxw, int max, int wraplen,
			     const char *pfx, const char *start, const char *end,
			     int flags)
{
  char *tagbuf, *valbuf, *t;
  int is_from = ((end - start) > 5 &&
		 ascii_strncasecmp (start, "from ", 5) == 0);

  /* only pass through folding machinery if necessary for sending,
     never wrap From_ headers on sending */
  if (!(flags & CH_DISPLAY) && (pfxw + max <= wraplen || is_from))
  {
    valbuf = mutt_substrdup (start, end);
    dprint(4,(debugfile,"mwoh: buf[%s%s] short enough, "
	      "max width = %d <= %d\n",
	      NONULL(pfx), valbuf, max, wraplen));
    if (pfx && *pfx)
      if (fputs (pfx, fp) == EOF)
	return -1;
    if (!(t = strchr (valbuf, ':')))
    {
      dprint (1, (debugfile, "mwoh: warning: header not in "
		  "'key: value' format!\n"));
      return 0;
    }
    if (print_val (fp, pfx, valbuf, flags, mutt_strlen (pfx)) < 0)
    {
      FREE(&valbuf);
      return -1;
    }
    FREE(&valbuf);
  }
  else
  {
    t = strchr (start, ':');
    if (!t || t > end)
    {
      dprint (1, (debugfile, "mwoh: warning: header not in "
		  "'key: value' format!\n"));
      return 0;
    }
    if (is_from)
    {
      tagbuf = NULL;
      valbuf = mutt_substrdup (start, end);
    }
    else
    {
      tagbuf = mutt_substrdup (start, t);
      /* skip over the colon separating the header field name and value */
      t = skip_email_wsp(t + 1);
      valbuf = mutt_substrdup (t, end);
    }
    dprint(4,(debugfile,"mwoh: buf[%s%s] too long, "
	      "max width = %d > %d\n",
	      NONULL(pfx), valbuf, max, wraplen));
    if (fold_one_header (fp, tagbuf, valbuf, pfx, wraplen, flags) < 0)
      return -1;
    FREE (&tagbuf);
    FREE (&valbuf);
  }
  return 0;
}