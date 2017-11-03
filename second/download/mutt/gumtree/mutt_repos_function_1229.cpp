static size_t convert_file_from_to (FILE *file,
				    const char *fromcodes, const char *tocodes,
				    char **fromcode, char **tocode, CONTENT *info)
{
  char *fcode = NULL;
  char **tcode;
  const char *c, *c1;
  size_t ret;
  int ncodes, i, cn;

  /* Count the tocodes */
  ncodes = 0;
  for (c = tocodes; c; c = c1 ? c1 + 1 : 0)
  {
    if ((c1 = strchr (c, ':')) == c)
      continue;
    ++ncodes;
  }

  /* Copy them */
  tcode = safe_malloc (ncodes * sizeof (char *));
  for (c = tocodes, i = 0; c; c = c1 ? c1 + 1 : 0, i++)
  {
    if ((c1 = strchr (c, ':')) == c)
      continue;
    tcode[i] = mutt_substrdup (c, c1);
  }

  ret = (size_t)(-1);
  if (fromcode)
  {
    /* Try each fromcode in turn */
    for (c = fromcodes; c; c = c1 ? c1 + 1 : 0)
    {
      if ((c1 = strchr (c, ':')) == c)
	continue;
      fcode = mutt_substrdup (c, c1);

      ret = convert_file_to (file, fcode, ncodes, (const char **)tcode,
			     &cn, info);
      if (ret != (size_t)(-1))
      {
	*fromcode = fcode;
	*tocode = tcode[cn];
	tcode[cn] = 0;
	break;
      }
      FREE (&fcode);
    }
  }
  else
  {
    /* There is only one fromcode */
    ret = convert_file_to (file, fromcodes, ncodes, (const char **)tcode,
			   &cn, info);
    if (ret != (size_t)(-1))
    {
      *tocode = tcode[cn];
      tcode[cn] = 0;
    }
  }

  /* Free memory */
  for (i = 0; i < ncodes; i++)
    FREE (&tcode[i]);

  FREE (&tcode);

  return ret;
}