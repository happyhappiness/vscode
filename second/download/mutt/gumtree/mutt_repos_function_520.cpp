static int invoke_dotlock (const char *path, int dummy, int flags, int retry)
{
  char cmd[LONG_STRING + _POSIX_PATH_MAX];
  char f[SHORT_STRING + _POSIX_PATH_MAX];
  char r[SHORT_STRING];
  
  if (flags & DL_FL_RETRY)
    snprintf (r, sizeof (r), "-r %d ", retry ? MAXLOCKATTEMPT : 0);
  
  mutt_quote_filename (f, sizeof (f), path);
  
  snprintf (cmd, sizeof (cmd),
	    "%s %s%s%s%s%s%s%s",
	    NONULL (MuttDotlock),
	    flags & DL_FL_TRY ? "-t " : "",
	    flags & DL_FL_UNLOCK ? "-u " : "",
	    flags & DL_FL_USEPRIV ? "-p " : "",
	    flags & DL_FL_FORCE ? "-f " : "",
	    flags & DL_FL_UNLINK ? "-d " : "",
	    flags & DL_FL_RETRY ? r : "",
	    f);
  
  return mutt_system (cmd);
}