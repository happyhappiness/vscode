static int undotlock_file (const char *path, int fd)
{
  return (invoke_dotlock(path, fd, DL_FL_USEPRIV | DL_FL_UNLOCK, 0) == DL_EX_OK ? 
	  0 : -1);
}