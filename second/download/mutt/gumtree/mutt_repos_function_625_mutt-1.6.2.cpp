static char **
be_include_messages (char *msg, char **buf, int *bufmax, int *buflen,
		     int pfx, int inc_hdrs)
{
  int offset, bytes, n;
  char tmp[LONG_STRING];

  while ((msg = strtok (msg, " ,")) != NULL)
  {
    if (mutt_atoi (msg, &n) == 0 && n > 0 && n <= Context->msgcount)
    {
      n--;

      /* add the attribution */
      if (Attribution)
      {
	mutt_make_string (tmp, sizeof (tmp) - 1, Attribution, Context, Context->hdrs[n]);
	strcat (tmp, "\n");	/* __STRCAT_CHECKED__ */
      }

      if (*bufmax == *buflen)
	safe_realloc ( &buf, sizeof (char *) * (*bufmax += 25));
      buf[(*buflen)++] = safe_strdup (tmp);

      bytes = Context->hdrs[n]->content->length;
      if (inc_hdrs)
      {
	offset = Context->hdrs[n]->offset;
	bytes += Context->hdrs[n]->content->offset - offset;
      }
      else
	offset = Context->hdrs[n]->content->offset;
      buf = be_snarf_data (Context->fp, buf, bufmax, buflen, offset, bytes,
			   pfx);

      if (*bufmax == *buflen)
	safe_realloc (&buf, sizeof (char *) * (*bufmax += 25));
      buf[(*buflen)++] = safe_strdup ("\n");
    }
    else
      printw (_("%d: invalid message number.\n"), n);
    msg = NULL;
  }
  return (buf);
}