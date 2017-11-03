void mutt_read_histfile (void)
{
  FILE *f;
  int line = 0, hclass, read;
  char *linebuf = NULL, *p;
  size_t buflen;

  if ((f = fopen (HistFile, "r")) == NULL)
    return;

  while ((linebuf = mutt_read_line (linebuf, &buflen, f, &line, 0)) != NULL)
  {
    read = 0;
    if (sscanf (linebuf, "%d:%n", &hclass, &read) < 1 || read == 0 ||
        *(p = linebuf + strlen (linebuf) - 1) != '|' || hclass < 0)
    {
      mutt_error (_("Bad history file format (line %d)"), line);
      break;
    }
    /* silently ignore too high class (probably newer mutt) */
    if (hclass >= HC_LAST)
      continue;
    *p = '\0';
    p = safe_strdup (linebuf + read);
    if (p)
    {
      mutt_convert_string (&p, "utf-8", Charset, 0);
      mutt_history_add (hclass, p, 0);
      FREE (&p);
    }
  }

  safe_fclose (&f);
  FREE (&linebuf);
}