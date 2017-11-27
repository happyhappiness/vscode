lt_dlhandle
lt_dlopen (filename)
     const char *filename;
{
  lt_dlhandle handle = 0;

  /* Just incase we missed a code path in try_dlopen() that reports
     an error, but forgets to reset handle... */
  if (try_dlopen (&handle, filename) != 0)
    return 0;

  return handle;
}