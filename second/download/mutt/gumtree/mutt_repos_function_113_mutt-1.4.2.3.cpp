void mutt_unlink (const char *s)
{
  FILE *f;
  struct stat sb;
  char buf[2048];
  
  if (stat (s, &sb) == 0)
  {
    if ((f = fopen (s, "r+")))
    {
      unlink (s);
      memset (buf, 0, sizeof (buf));
      while (sb.st_size > 0)
      {
	fwrite (buf, 1, MIN (sizeof (buf), sb.st_size), f);
	sb.st_size -= MIN (sizeof (buf), sb.st_size);
      }
      fclose (f);
    }
  }
}