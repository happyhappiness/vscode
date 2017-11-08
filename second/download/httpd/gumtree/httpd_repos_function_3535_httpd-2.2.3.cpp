static int
pcregrep(FILE *in, char *name)
{
int rc = 1;
int linenumber = 0;
int count = 0;
int offsets[99];
char buffer[BUFSIZ];

while (fgets(buffer, sizeof(buffer), in) != NULL)
  {
  BOOL match = FALSE;
  int i;
  int length = (int)strlen(buffer);
  if (length > 0 && buffer[length-1] == '\n') buffer[--length] = 0;
  linenumber++;

  for (i = 0; !match && i < pattern_count; i++)
    {
    match = pcre_exec(pattern_list[i], hints_list[i], buffer, length, 0, 0,
      offsets, 99) >= 0;
    if (match && whole_lines && offsets[1] != length) match = FALSE;
    }

  if (match != invert)
    {
    if (count_only) count++;

    else if (filenames_only)
      {
      fprintf(stdout, "%s\n", (name == NULL)? "<stdin>" : name);
      return 0;
      }

    else if (silent) return 0;

    else
      {
      if (name != NULL) fprintf(stdout, "%s:", name);
      if (number) fprintf(stdout, "%d:", linenumber);
      fprintf(stdout, "%s\n", buffer);
      }

    rc = 0;
    }
  }

if (count_only)
  {
  if (name != NULL) fprintf(stdout, "%s:", name);
  fprintf(stdout, "%d\n", count);
  }

return rc;
}