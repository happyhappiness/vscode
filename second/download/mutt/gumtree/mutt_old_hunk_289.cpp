  }

  safe_fclose (&f);
  FREE (&linebuf);
}

static void shrink_histfile (void)
{
  char tmpfname[_POSIX_PATH_MAX];
  FILE *f, *tmp = NULL;
  int n[HC_LAST] = { 0 };
  int line, hclass;
  char *linebuf = NULL;
  size_t buflen;

  if ((f = fopen (HistFile, "r")) == NULL)
    return;

  line = 0;
  while ((linebuf = mutt_read_line (linebuf, &buflen, f, &line, 0)) != NULL)
  {
    if (sscanf (linebuf, "%d", &hclass) < 1 || hclass < 0)
    {
      mutt_error (_("Bad history file format (line %d)"), line);
      goto cleanup;
    }
    /* silently ignore too high class (probably newer mutt) */
    if (hclass >= HC_LAST)
      continue;
    n[hclass]++;
  }

  for(hclass = HC_FIRST; hclass < HC_LAST; hclass++)
    if (n[hclass] > SaveHist)
    {
      mutt_mktemp (tmpfname, sizeof (tmpfname));
      if ((tmp = safe_fopen (tmpfname, "w+")) == NULL)
        mutt_perror (tmpfname);
      break;
    }

  if (tmp != NULL)
  {
    rewind (f);
    line = 0;
    while ((linebuf = mutt_read_line (linebuf, &buflen, f, &line, 0)) != NULL)
    {
      if (sscanf (linebuf, "%d", &hclass) < 1 || hclass < 0)
      {
        mutt_error (_("Bad history file format (line %d)"), line);
        goto cleanup;
      }
      /* silently ignore too high class (probably newer mutt) */
      if (hclass >= HC_LAST)
	continue;
      if (n[hclass]-- <= SaveHist)
        fprintf (tmp, "%s\n", linebuf);
    }
  }

cleanup:
