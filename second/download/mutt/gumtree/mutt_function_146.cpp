static int dotlock_file (const char *path, int fd, int retry)
{
  int r;
  int flags = DL_FL_USEPRIV | DL_FL_RETRY;

  if (retry) retry = 1;

retry_lock:
  if ((r = invoke_dotlock(path, fd, flags, retry)) == DL_EX_EXIST)
  {
    if (!option (OPTNOCURSES))
    {
      char msg[LONG_STRING];
      
      snprintf(msg, sizeof(msg), _("Lock count exceeded, remove lock for %s?"),
	       path);
      if(retry && mutt_yesorno(msg, M_YES) == M_YES)
      {
	flags |= DL_FL_FORCE;
	retry--;
	mutt_clear_error ();
	goto retry_lock;
      }
    } 
    else
    {
      mutt_error ( _("Can't dotlock %s.\n"), path);
    }
  }
  return (r == DL_EX_OK ? 0 : -1);
}