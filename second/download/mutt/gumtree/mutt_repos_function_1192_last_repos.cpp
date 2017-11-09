static int
dotlock_deference_symlink (char *d, size_t l, const char *path)
{
  struct stat sb;
  char realpath[_POSIX_PATH_MAX];
  const char *pathptr = path;
  int count = 0;
  
  while (count++ < MAXLINKS)
  {
    if (lstat (pathptr, &sb) == -1)
    {
      /* perror (pathptr); */
      return -1;
    }
    
    if (S_ISLNK (sb.st_mode))
    {
      char linkfile[_POSIX_PATH_MAX];
      char linkpath[_POSIX_PATH_MAX];
      int len;

      if ((len = readlink (pathptr, linkfile, sizeof (linkfile) - 1)) == -1)
      {
	/* perror (pathptr); */
	return -1;
      }
      
      linkfile[len] = '\0';
      dotlock_expand_link (linkpath, pathptr, linkfile);
      strfcpy (realpath, linkpath, sizeof (realpath));
      pathptr = realpath;
    }
    else
      break;
  }

  strfcpy (d, pathptr, l);
  return 0;
}