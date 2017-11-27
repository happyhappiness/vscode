int read_types_list (void)
{
  const char *file;
  FILE *fh;

  file = global_option_get ("TypesDB");
  if (file == NULL)
  {
    ERROR ("global_option_get (\"TypesDB\") returned NULL.");
    return (-1);
  }

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