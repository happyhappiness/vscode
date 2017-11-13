static void save_history (history_class_t hclass, const char *s)
{
  static int n = 0;
  FILE *f;
  char *tmp, *p;

  if (!s || !*s)  /* This shouldn't happen, but it's safer. */
    return;

  if ((f = fopen (HistFile, "a")) == NULL)
  {
    mutt_perror ("fopen");
    return;
  }

  tmp = safe_strdup (s);
  mutt_convert_string (&tmp, Charset, "utf-8", 0);

  /* Format of a history item (1 line): "<histclass>:<string>|".
     We add a '|' in order to avoid lines ending with '\'. */
  fprintf (f, "%d:", (int) hclass);
  for (p = tmp; *p; p++)
  {
    /* Don't copy \n as a history item must fit on one line. The string
       shouldn't contain such a character anyway, but as this can happen
       in practice, we must deal with that. */
    if (*p != '\n')
      putc ((unsigned char) *p, f);
  }
  fputs ("|\n", f);

  safe_fclose (&f);
  FREE (&tmp);

  if (--n < 0)
  {
    n = SaveHist;
    shrink_histfile();
  }
}