CONTENT *mutt_get_content_info (const char *fname, BODY *b)
{
  CONTENT *info;
  CONTENT_STATE state;
  FILE *fp = NULL;
  char *fromcode = NULL;
  char *tocode;
  char buffer[100];
  char chsbuf[STRING];
  size_t r;

  struct stat sb;

  if(b && !fname) fname = b->filename;

  if (stat (fname, &sb) == -1)
  {
    mutt_error (_("Can't stat %s: %s"), fname, strerror (errno));
    return NULL;
  }

  if (!S_ISREG(sb.st_mode))
  {
    mutt_error (_("%s isn't a regular file."), fname);
    return NULL;
  }

  if ((fp = fopen (fname, "r")) == NULL)
  {
    dprint (1, (debugfile, "mutt_get_content_info: %s: %s (errno %d).\n",
		fname, strerror (errno), errno));
    return (NULL);
  }

  info = safe_calloc (1, sizeof (CONTENT));
  memset (&state, 0, sizeof (state));

  if (b != NULL && b->type == TYPETEXT && (!b->noconv && !b->force_charset))
  {
    char *chs = mutt_get_parameter ("charset", b->parameter);
    char *fchs = b->use_disp ? ((AttachCharset && *AttachCharset) ?
                                AttachCharset : Charset) : Charset;
    if (Charset && (chs || SendCharset) &&
        convert_file_from_to (fp, fchs, chs ? chs : SendCharset,
                              &fromcode, &tocode, info) != (size_t)(-1))
    {
      if (!chs)
      {
	mutt_canonical_charset (chsbuf, sizeof (chsbuf), tocode);
	mutt_set_parameter ("charset", chsbuf, &b->parameter);
      }
      FREE (&b->charset);
      b->charset = fromcode;
      FREE (&tocode);
      safe_fclose (&fp);
      return info;
    }
  }

  rewind (fp);
  while ((r = fread (buffer, 1, sizeof(buffer), fp)))
    update_content_info (info, &state, buffer, r);
  update_content_info (info, &state, 0, 0);

  safe_fclose (&fp);

  if (b != NULL && b->type == TYPETEXT && (!b->noconv && !b->force_charset))
    mutt_set_parameter ("charset", (!info->hibin ? "us-ascii" :
				    Charset  && !mutt_is_us_ascii (Charset) ? Charset : "unknown-8bit"),
			&b->parameter);

  return info;
}