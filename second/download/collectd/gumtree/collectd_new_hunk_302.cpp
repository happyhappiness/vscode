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

