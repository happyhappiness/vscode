int main (int argc, char **argv)
{
  int i;
  char *p;
  struct utsname utsname;

  /* first, drop privileges */
  
  if (dotlock_init_privs () == -1)
    return DL_EX_ERROR;


  /* determine the system's host name */
  
  uname (&utsname);
  if (!(Hostname = strdup (utsname.nodename)))	/* __MEM_CHECKED__ */
    return DL_EX_ERROR;
  if ((p = strchr (Hostname, '.')))
    *p = '\0';


  /* parse the command line options. */
  DotlockFlags = 0;
  
  while ((i = getopt (argc, argv, "dtfupr:")) != EOF)
  {
    switch (i)
    {
      /* actions, mutually exclusive */
      case 't': check_flags (DotlockFlags); DotlockFlags |= DL_FL_TRY; break;
      case 'd': check_flags (DotlockFlags); DotlockFlags |= DL_FL_UNLINK; break;
      case 'u': check_flags (DotlockFlags); DotlockFlags |= DL_FL_UNLOCK; break;

      /* other flags */
      case 'f': DotlockFlags |= DL_FL_FORCE; break;
      case 'p': DotlockFlags |= DL_FL_USEPRIV; break;
      case 'r': DotlockFlags |= DL_FL_RETRY; Retry = atoi (optarg); break;
      
      default: usage (argv[0]);
    }
  }

  if (optind == argc || Retry < 0)
    usage (argv[0]);

  return dotlock_dispatch (argv[optind], -1);
}