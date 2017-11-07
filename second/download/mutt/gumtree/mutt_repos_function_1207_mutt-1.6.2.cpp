static size_t convert_file_to (FILE *file, const char *fromcode,
			       int ncodes, const char **tocodes,
			       int *tocode, CONTENT *info)
{
#ifdef HAVE_ICONV
  iconv_t cd1, *cd;
  char bufi[256], bufu[512], bufo[4 * sizeof (bufi)];
  ICONV_CONST char *ib, *ub;
  char *ob;
  size_t ibl, obl, ubl, ubl1, n, ret;
  int i;
  CONTENT *infos;
  CONTENT_STATE *states;
  size_t *score;

  cd1 = mutt_iconv_open ("utf-8", fromcode, 0);
  if (cd1 == (iconv_t)(-1))
    return -1;

  cd     = safe_calloc (ncodes, sizeof (iconv_t));
  score  = safe_calloc (ncodes, sizeof (size_t));
  states = safe_calloc (ncodes, sizeof (CONTENT_STATE));
  infos  = safe_calloc (ncodes, sizeof (CONTENT));

  for (i = 0; i < ncodes; i++)
    if (ascii_strcasecmp (tocodes[i], "utf-8"))
      cd[i] = mutt_iconv_open (tocodes[i], "utf-8", 0);
    else
      /* Special case for conversion to UTF-8 */
      cd[i] = (iconv_t)(-1), score[i] = (size_t)(-1);

  rewind (file);
  ibl = 0;
  for (;;)
  {

    /* Try to fill input buffer */
    n = fread (bufi + ibl, 1, sizeof (bufi) - ibl, file);
    ibl += n;

    /* Convert to UTF-8 */
    ib = bufi;
    ob = bufu, obl = sizeof (bufu);
    n = iconv (cd1, ibl ? &ib : 0, &ibl, &ob, &obl);
    assert (n == (size_t)(-1) || !n || ICONV_NONTRANS);
    if (n == (size_t)(-1) &&
	((errno != EINVAL && errno != E2BIG) || ib == bufi))
    {
      assert (errno == EILSEQ ||
	      (errno == EINVAL && ib == bufi && ibl < sizeof (bufi)));
      ret = (size_t)(-1);
      break;
    }
    ubl1 = ob - bufu;

    /* Convert from UTF-8 */
    for (i = 0; i < ncodes; i++)
      if (cd[i] != (iconv_t)(-1) && score[i] != (size_t)(-1))
      {
	ub = bufu, ubl = ubl1;
	ob = bufo, obl = sizeof (bufo);
	n = iconv (cd[i], (ibl || ubl) ? &ub : 0, &ubl, &ob, &obl);
	if (n == (size_t)(-1))
	{
	  assert (errno == E2BIG ||
		  (BUGGY_ICONV && (errno == EILSEQ || errno == ENOENT)));
	  score[i] = (size_t)(-1);
	}
	else
	{
	  score[i] += n;
	  update_content_info (&infos[i], &states[i], bufo, ob - bufo);
	}
      }
      else if (cd[i] == (iconv_t)(-1) && score[i] == (size_t)(-1))
	/* Special case for conversion to UTF-8 */
	update_content_info (&infos[i], &states[i], bufu, ubl1);

    if (ibl)
      /* Save unused input */
      memmove (bufi, ib, ibl);
    else if (!ubl1 && ib < bufi + sizeof (bufi))
    {
      ret = 0;
      break;
    }
  }

  if (!ret)
  {
    /* Find best score */
    ret = (size_t)(-1);
    for (i = 0; i < ncodes; i++)
    {
      if (cd[i] == (iconv_t)(-1) && score[i] == (size_t)(-1))
      {
	/* Special case for conversion to UTF-8 */
	*tocode = i;
	ret = 0;
	break;
      }
      else if (cd[i] == (iconv_t)(-1) || score[i] == (size_t)(-1))
	continue;
      else if (ret == (size_t)(-1) || score[i] < ret)
      {
	*tocode = i;
	ret = score[i];
	if (!ret)
	  break;
      }
    }
    if (ret != (size_t)(-1))
    {
      memcpy (info, &infos[*tocode], sizeof(CONTENT));
      update_content_info (info, &states[*tocode], 0, 0); /* EOF */
    }
  }

  for (i = 0; i < ncodes; i++)
    if (cd[i] != (iconv_t)(-1))
      iconv_close (cd[i]);

  iconv_close (cd1);
  FREE (&cd);
  FREE (&infos);
  FREE (&score);
  FREE (&states);

  return ret;
#else
  return -1;
#endif /* !HAVE_ICONV */
}