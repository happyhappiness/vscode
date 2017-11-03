static void mhs_write_one_sequence (FILE * fp, struct mh_sequences *mhs,
				    short f, const char *tag)
{
  int i;
  int first, last;
  fprintf (fp, "%s:", tag);

  first = -1;
  last = -1;

  for (i = 0; i <= mhs->max; i++)
  {
    if ((mhs_check (mhs, i) & f))
    {
      if (first < 0)
	first = i;
      else
	last = i;
    }
    else if (first >= 0)
    {
      if (last < 0)
	fprintf (fp, " %d", first);
      else
	fprintf (fp, " %d-%d", first, last);

      first = -1;
      last = -1;
    }
  }

  if (first >= 0)
  {
    if (last < 0)
      fprintf (fp, " %d", first);
    else
      fprintf (fp, " %d-%d", first, last);
  }

  fputc ('\n', fp);
}