void set_advisor_read_lock(const char *filename)
{
  FILE *lockfile;
  int error = 0;
  int res;

  do {
    lockfile = fopen(filename, "wb");
  } while((lockfile == NULL) && ((error = errno) == EINTR));
  if(lockfile == NULL) {
    logmsg("Error creating lock file %s error: %d %s",
           filename, error, strerror(error));
    return;
  }

  do {
    res = fclose(lockfile);
  } while(res && ((error = errno) == EINTR));
  if(res)
    logmsg("Error closing lock file %s error: %d %s",
           filename, error, strerror(error));
}