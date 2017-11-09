int safe_symlink(const char *oldpath, const char *newpath)
{
  struct stat osb, nsb;

  if(!oldpath || !newpath)
    return -1;
  
  if(unlink(newpath) == -1 && errno != ENOENT)
    return -1;
  
  if (oldpath[0] == '/')
  {
    if (symlink (oldpath, newpath) == -1)
      return -1;
  }
  else
  {
    char abs_oldpath[_POSIX_PATH_MAX];

    if ((getcwd (abs_oldpath, sizeof abs_oldpath) == NULL) ||
	(strlen (abs_oldpath) + 1 + strlen (oldpath) + 1 > sizeof abs_oldpath))
    return -1;
  
    strcat (abs_oldpath, "/");		/* __STRCAT_CHECKED__ */
    strcat (abs_oldpath, oldpath);	/* __STRCAT_CHECKED__ */
    if (symlink (abs_oldpath, newpath) == -1)
      return -1;
  }

  if(stat(oldpath, &osb) == -1 || stat(newpath, &nsb) == -1
     || compare_stat(&osb, &nsb) == -1)
  {
    unlink(newpath);
    return -1;
  }
  
  return 0;
}