static char **
be_snarf_file (const char *path, char **buf, int *max, int *len, int verbose)
{
  FILE *f;
  char tmp[LONG_STRING];
  struct stat sb;
  
  if ((f = fopen (path, "r")))
  {
    fstat (fileno (f), &sb);
    buf = be_snarf_data (f, buf, max, len, 0, sb.st_size, 0);
    if (verbose)
    {
      snprintf(tmp, sizeof(tmp), "\"%s\" %lu bytes\n", path, (unsigned long) sb.st_size);
      addstr(tmp);
    }
    safe_fclose (&f);
  }
  else
  {
    snprintf(tmp, sizeof(tmp), "%s: %s\n", path, strerror(errno));
    addstr(tmp);
  }
  return (buf);
}