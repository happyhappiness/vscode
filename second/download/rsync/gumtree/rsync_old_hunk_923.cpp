static void tls_usage(int ret)
{
  FILE *F = ret ? stderr : stdout;
  fprintf(F,"usage: " PROGRAM " [OPTIONS] FILE ...\n");
  fprintf(F,"Trivial file listing program for portably checking rsync\n");
  fprintf(F,"\nOptions:\n");
#ifdef SUPPORT_XATTRS
  fprintf(F," -f, --fake-super            display attributes including fake-super xattrs\n");
#endif
  fprintf(F," -h, --help                  show this help\n");
  exit(ret);
}
