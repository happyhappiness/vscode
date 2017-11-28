static lt_module
vm_open (lt_user_data loader_data LT__UNUSED, const char *filename,
         lt_dladvise advise LT__UNUSED)
{
  lt_module	module	   = 0;
  char		*ext;
  char		wpath[MAX_PATH];
  size_t	len;

  if (!filename)
    {
      /* Get the name of main module */
      *wpath = 0;
      GetModuleFileName (NULL, wpath, sizeof (wpath));
      filename = wpath;
    }
  else
    {
      len = LT_STRLEN (filename);

      if (len >= MAX_PATH)
        {
	  LT__SETERROR (CANNOT_OPEN);
	  return 0;
	}

#if HAVE_DECL_CYGWIN_CONV_PATH
      if (cygwin_conv_path (CCP_POSIX_TO_WIN_A, filename, wpath, MAX_PATH))
	{
	  LT__SETERROR (CANNOT_OPEN);
	  return 0;
	}
      len = 0;
#elif defined __CYGWIN__
      cygwin_conv_to_full_win32_path (filename, wpath);
      len = 0;
#else
      strcpy(wpath, filename);
#endif

      ext = strrchr (wpath, '.');
      if (!ext)
	{
	  /* Append a '.' to stop Windows from adding an
	     implicit '.dll' extension. */
	  if (!len)
	    len = strlen (wpath);

	  if (len + 1 >= MAX_PATH)
	    {
	      LT__SETERROR (CANNOT_OPEN);
	      return 0;
	    }

	  wpath[len] = '.';
	  wpath[len+1] = '\0';
	}
    }

  {
    /* Silence dialog from LoadLibrary on some failures. */
    DWORD errormode = getthreaderrormode ();
    DWORD last_error;

    setthreaderrormode (errormode | SEM_FAILCRITICALERRORS, NULL);

    module = LoadLibrary (wpath);

    /* Restore the error mode. */
    last_error = GetLastError ();
    setthreaderrormode (errormode, NULL);
    SetLastError (last_error);
  }

  /* libltdl expects this function to fail if it is unable
     to physically load the library.  Sadly, LoadLibrary
     will search the loaded libraries for a match and return
     one of them if the path search load fails.

     We check whether LoadLibrary is returning a handle to
     an already loaded module, and simulate failure if we
     find one. */
  {
    lt_dlhandle cur = 0;

    while ((cur = lt_dlhandle_iterate (iface_id, cur)))
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
      }

    if (!module)
      LOADLIB_SETERROR (CANNOT_OPEN);
    else if (cur)
      {
        LT__SETERROR (CANNOT_OPEN);
        module = 0;
      }
  }

  return module;
}