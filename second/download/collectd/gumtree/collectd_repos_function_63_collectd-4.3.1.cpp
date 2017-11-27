static int
find_handle_callback (filename, data, ignored)
     char *filename;
     lt_ptr data;
     lt_ptr ignored;
{
  lt_dlhandle  *handle		= (lt_dlhandle *) data;
  int		notfound	= access (filename, R_OK);

  /* Bail out if file cannot be read...  */
  if (notfound)
    return 0;

  /* Try to dlopen the file, but do not continue searching in any
     case.  */
  if (tryall_dlopen (handle, filename) != 0)
    *handle = 0;

  return 1;
}