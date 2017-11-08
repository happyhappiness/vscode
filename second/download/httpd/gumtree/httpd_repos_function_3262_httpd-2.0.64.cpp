static int
grep_or_recurse(char *filename, BOOL recurse, BOOL show_filenames,
  BOOL only_one_at_top)
{
int rc = 1;
int sep;
FILE *in;

/* If the file is a directory and we are recursing, scan each file within it.
The scanning code is localized so it can be made system-specific. */

if ((sep = isdirectory(filename)) != 0 && recurse)
  {
  char buffer[1024];
  char *nextfile;
  directory_type *dir = opendirectory(filename);

  if (dir == NULL)
    {
    fprintf(stderr, "pcregrep: Failed to open directory %s: %s\n", filename,
      strerror(errno));
    return 2;
    }

  while ((nextfile = readdirectory(dir)) != NULL)
    {
    int frc;
    sprintf(buffer, "%.512s%c%.128s", filename, sep, nextfile);
    frc = grep_or_recurse(buffer, recurse, TRUE, FALSE);
    if (frc == 0 && rc == 1) rc = 0;
    }

  closedirectory(dir);
  return rc;
  }

/* If the file is not a directory, or we are not recursing, scan it. If this is
the first and only argument at top level, we don't show the file name.
Otherwise, control is via the show_filenames variable. */

in = fopen(filename, "r");
if (in == NULL)
  {
  fprintf(stderr, "pcregrep: Failed to open %s: %s\n", filename, strerror(errno));
  return 2;
  }

rc = pcregrep(in, (show_filenames && !only_one_at_top)? filename : NULL);
fclose(in);
return rc;
}