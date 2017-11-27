int read_types_list (const char *file)
{
  FILE *fh;

  if (file == NULL)
    return (-1);

  fh = fopen (file, "r");
  if (fh == NULL)
  {
    char errbuf[1024];
    ERROR ("open (%s) failed: %s", 
	file, sstrerror (errno, errbuf, sizeof (errbuf)));
    return (-1);
  }

  parse_file (fh);

  fclose (fh);
  fh = NULL;

  DEBUG ("Done parsing `%s'", file);

  return (0);
}