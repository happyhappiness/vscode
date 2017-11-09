static int
dotlock_unlock (const char *realpath)
{
  char lockfile[_POSIX_PATH_MAX + LONG_STRING];
  int i;

  snprintf (lockfile, sizeof (lockfile), "%s.lock",
	   realpath);
  
  BEGIN_PRIVILEGED ();
  i = unlink (lockfile);
  END_PRIVILEGED ();
  
  if (i == -1)
    return DL_EX_ERROR;
  
  return DL_EX_OK;
}