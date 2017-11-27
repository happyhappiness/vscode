static void parse_file (FILE *fh)
{
  char buf[4096];
  size_t buf_len;

  while (fgets (buf, sizeof (buf), fh) != NULL)
  {
    buf_len = strlen (buf);

    if (buf_len >= 4095)
    {
      NOTICE ("Skipping line with more than 4095 characters.");
      do
      {
	if (fgets (buf, sizeof (buf), fh) == NULL)
	  break;
	buf_len = strlen (buf);
      } while (buf_len >= 4095);
      continue;
    } /* if (buf_len >= 4095) */

    if ((buf_len == 0) || (buf[0] == '#'))
      continue;

    while ((buf_len > 0) && ((buf[buf_len - 1] == '\n')
	  || (buf[buf_len - 1] == '\r')))
      buf[--buf_len] = '\0';

    if (buf_len == 0)
      continue;

    parse_line (buf);
  } /* while (fgets) */
}