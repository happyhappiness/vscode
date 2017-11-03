int main (int argc, char *argv[])
{
  int c;
  FILE *f;

  if ((Progname = strrchr (argv[0], '/')))
    Progname++;
  else
    Progname = argv[0];
  
  while ((c = getopt (argc, argv, "cmsd")) != EOF)
  {
    switch (c)
    {
      case 'c': OutputFormat = F_CONF; break;
      case 'm': OutputFormat = F_MAN; break;
      case 's': OutputFormat = F_SGML; break;
      case 'd': Debug++; break;
      default: 
      {
	fprintf (stderr, "%s: bad command line parameter.\n", Progname);
	exit (1);
      }
    }
  }

  if (optind != argc)
  {
    if ((f = fopen (argv[optind], "r")) == NULL)
    {
      fprintf (stderr, "%s: Can't open %s (%s).\n",
	       Progname, argv[optind], strerror (errno));
      exit (1);
    }
  }
  else 
    f = stdin;

  switch (OutputFormat)
  {
    case F_CONF: 
    case F_MAN:  
    case F_SGML: makedoc (f, stdout); break;
    default:
    {
      fprintf (stderr, "%s: No output format specified.\n",
	       Progname);
      exit (1);
    }
  }
  
  if (f != stdin)
    fclose (f);

  return 0;
}