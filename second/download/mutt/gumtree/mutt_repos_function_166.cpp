void mutt_unlink (const char *s)
{
  int fd;
  int flags;
  FILE *f;
  struct stat sb, sb2;
  char buf[2048];

  /* Defend against symlink attacks */
  
#ifdef O_NOFOLLOW 
  flags = O_RDWR | O_NOFOLLOW;
#else
  flags = O_RDWR;
#endif
  
  if (lstat (s, &sb) == 0 && S_ISREG(sb.st_mode))
  {
    if ((fd = open (s, flags)) < 0)
      return;
    
    if ((fstat (fd, &sb2) != 0) || !S_ISREG (sb2.st_mode) 
	|| (sb.st_dev != sb2.st_dev) || (sb.st_ino != sb2.st_ino))
    {
      close (fd);
      return;
    }
    
    if ((f = fdopen (fd, "r+")))
    {
      unlink (s);
      memset (buf, 0, sizeof (buf));
      while (sb.st_size > 0)
      {
	fwrite (buf, 1, MIN (sizeof (buf), sb.st_size), f);
	sb.st_size -= MIN (sizeof (buf), sb.st_size);
      }
      safe_fclose (&f);
    }
  }
}