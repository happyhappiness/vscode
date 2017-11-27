static lt_module
sys_wll_open (loader_data, filename)
     lt_user_data loader_data;
     const char *filename;
{
  lt_dlhandle	cur;
  lt_module	module	   = 0;
  const char   *errormsg   = 0;
  char	       *searchname = 0;
  char	       *ext;
  char		self_name_buf[MAX_PATH];

  if (!filename)
    {
      /* Get the name of main module */
      *self_name_buf = 0;
      GetModuleFileName (NULL, self_name_buf, sizeof (self_name_buf));
      filename = ext = self_name_buf;
    }
  else
    {
      ext = strrchr (filename, '.');
    }

  if (ext)
    {
      /* FILENAME already has an extension. */
      searchname = lt_estrdup (filename);
    }
  else
    {
      /* Append a `.' to stop Windows from adding an
	 implicit `.dll' extension. */
      searchname = LT_EMALLOC (char, 2+ LT_STRLEN (filename));
      if (searchname)
	sprintf (searchname, "%s.", filename);
    }
  if (!searchname)
    return 0;

  {
    /* Silence dialog from LoadLibrary on some failures.
       No way to get the error mode, but to set it,
       so set it twice to preserve any previous flags. */
    UINT errormode = SetErrorMode(SEM_FAILCRITICALERRORS);
    SetErrorMode(errormode | SEM_FAILCRITICALERRORS);

#if defined(__CYGWIN__)
    {
      char wpath[MAX_PATH];
      cygwin_conv_to_full_win32_path (searchname, wpath);
      module = LoadLibrary (wpath);
    }
#else
    module = LoadLibrary (searchname);
#endif

    /* Restore the error mode. */
    SetErrorMode(errormode);
  }

  LT_DLFREE (searchname);

  /* libltdl expects this function to fail if it is unable
     to physically load the library.  Sadly, LoadLibrary
     will search the loaded libraries for a match and return
     one of them if the path search load fails.

     We check whether LoadLibrary is returning a handle to
     an already loaded module, and simulate failure if we
     find one. */
  LT_DLMUTEX_LOCK ();
  cur = handles;
  while (cur)
    {
      if (!cur->module)
	{
	  cur = 0;
	  break;
	}

      if (cur->module == module)
	{
	  break;
	}

      cur = cur->next;
  }
  LT_DLMUTEX_UNLOCK ();

  if (cur || !module)
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (CANNOT_OPEN));
      module = 0;
    }

  return module;
}