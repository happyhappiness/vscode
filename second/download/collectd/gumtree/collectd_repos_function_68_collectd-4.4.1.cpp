static int
free_vars (dlname, oldname, libdir, deplibs)
     char *dlname;
     char *oldname;
     char *libdir;
     char *deplibs;
{
  LT_DLFREE (dlname);
  LT_DLFREE (oldname);
  LT_DLFREE (libdir);
  LT_DLFREE (deplibs);

  return 0;
}