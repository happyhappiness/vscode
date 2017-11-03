static void 
usage (const char *av0)
{
  fprintf (stderr, "dotlock [Mutt %s (%s)]\n", VERSION, ReleaseDate);
  fprintf (stderr, "usage: %s [-t|-f|-u|-d] [-p] [-r <retries>] file\n",
	  av0);

  fputs ("\noptions:"
	"\n  -t\t\ttry"
	"\n  -f\t\tforce"
	"\n  -u\t\tunlock"
	"\n  -d\t\tunlink"
	"\n  -p\t\tprivileged"
#ifndef USE_SETGID
	" (ignored)"
#endif
	"\n  -r <retries>\tRetry locking"
	"\n", stderr);
  
  exit (DL_EX_ERROR);
}