int main (int argc, char * const argv[])
{
  int c;
  
  short version = 2;
  short secring = 0;
  
  const char *_kring = NULL;
  char *env_pgppath, *env_home;

  char pgppath[_POSIX_PATH_MAX];
  char kring[_POSIX_PATH_MAX];

  while ((c = getopt (argc, argv, "f25sk:S")) != EOF)
  {
    switch (c)
    {
      case 'S':
      {
	dump_signatures = 1;
	break;
      }

      case 'f':
      {
	dump_fingerprints = 1;
	break;
      }

      case 'k':
      {
	_kring = optarg;
	break;
      }
      
      case '2': case '5':
      {
	version = c - '0';
	break;
      }
      
      case 's':
      {
	secring = 1;
	break;
      }
    
      default:
      {
	fprintf (stderr, "usage: %s [-k <key ring> | [-2 | -5] [ -s] [-S] [-f]] [hints]\n",
		 argv[0]);
	exit (1);
      }
    }
  }

  if (_kring)
    strfcpy (kring, _kring, sizeof (kring));
  else
  {
    if ((env_pgppath = getenv ("PGPPATH")))
      strfcpy (pgppath, env_pgppath, sizeof (pgppath));
    else if ((env_home = getenv ("HOME")))
      snprintf (pgppath, sizeof (pgppath), "%s/.pgp", env_home);
    else
    {
      fprintf (stderr, "%s: Can't determine your PGPPATH.\n", argv[0]);
      exit (1);
    }
    
    if (secring)
      snprintf (kring, sizeof (kring), "%s/secring.%s", pgppath, version == 2 ? "pgp" : "skr");
    else
      snprintf (kring, sizeof (kring), "%s/pubring.%s", pgppath, version == 2 ? "pgp" : "pkr");
  }
  
  pgpring_find_candidates (kring, (const char**) argv + optind, argc - optind);
    
  return 0;
}