 * 
 */

static void 
usage (const char *av0)
{
  fprintf (stderr, "dotlock [Mutt %s (%s)]\n", MUTT_VERSION, ReleaseDate);
  fprintf (stderr, "usage: %s [-t|-f|-u|-d] [-p] [-r <retries>] file\n",
	  av0);

  fputs ("\noptions:"
	"\n  -t\t\ttry"
	"\n  -f\t\tforce"
