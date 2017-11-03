static int be_barf_file (const char *path, char **buf, int buflen)
{
  FILE *f;
  int i;
  
  if ((f = fopen (path, "w")) == NULL)		/* __FOPEN_CHECKED__ */
  {
    addstr (strerror (errno));
    addch ('\n');
    return (-1);
  }
  for (i = 0; i < buflen; i++) fputs (buf[i], f);
  if (fclose (f) == 0) return 0;
  printw ("fclose: %s\n", strerror (errno));
  return (-1);
}