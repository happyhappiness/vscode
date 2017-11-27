      while (handles && LT_DLIS_RESIDENT (handles))
	{
	  handles = handles->next;
	}

      /* close all modules */
      for (level = 1; handles; ++level)
	{
	  lt_dlhandle cur = handles;
	  int saw_nonresident = 0;

	  while (cur)
	    {
	      lt_dlhandle tmp = cur;
	      cur = cur->next;
	      if (!LT_DLIS_RESIDENT (tmp))
		saw_nonresident = 1;
	      if (!LT_DLIS_RESIDENT (tmp) && tmp->info.ref_count <= level)
		{
		  if (lt_dlclose (tmp))
		    {
		      ++errors;
		    }
		  /* Make sure that the handle pointed to by 'cur' still exists.
		     lt_dlclose recursively closes dependent libraries which removes
		     them from the linked list.  One of these might be the one
		     pointed to by 'cur'.  */
		  if (cur)
		    {
		      for (tmp = handles; tmp; tmp = tmp->next)
			if (tmp == cur)
			  break;
		      if (! tmp)
			cur = handles;
		    }
		}
	    }
	  /* done if only resident modules are left */
	  if (!saw_nonresident)
	    break;
	}

      /* close all loaders */
      while (loader)
	{
	  lt_dlloader *next = loader->next;
	  lt_user_data data = loader->dlloader_data;
	  if (loader->dlloader_exit && loader->dlloader_exit (data))
	    {
	      ++errors;
	    }

	  LT_DLMEM_REASSIGN (loader, next);
	}
      loaders = 0;
    }

 done:
  LT_DLMUTEX_UNLOCK ();
  return errors;
}

static int
tryall_dlopen (handle, filename, useloader)
     lt_dlhandle *handle;
     const char *filename;
     const char *useloader;
{
  lt_dlhandle	 cur;
  lt_dlloader   *loader;
  const char	*saved_error;
  int		 errors		= 0;

  LT_DLMUTEX_GETERROR (saved_error);
  LT_DLMUTEX_LOCK ();

  cur	 = handles;
  loader = loaders;

  /* check whether the module was already opened */
  while (cur)
    {
      /* try to dlopen the program itself? */
      if (!cur->info.filename && !filename)
	{
	  break;
	}

      if (cur->info.filename && filename
	  && strcmp (cur->info.filename, filename) == 0)
	{
	  break;
	}

      cur = cur->next;
    }

  if (cur)
    {
      ++cur->info.ref_count;
      *handle = cur;
      goto done;
    }

  cur = *handle;
  if (filename)
    {
      /* Comment out the check of file permissions using access.
	 This call seems to always return -1 with error EACCES.
      */
      /* We need to catch missing file errors early so that
	 file_not_found() can detect what happened.
      if (access (filename, R_OK) != 0)
	{
	  LT_DLMUTEX_SETERROR (LT_DLSTRERROR (FILE_NOT_FOUND));
	  ++errors;
	  goto done;
	} */

      cur->info.filename = lt_estrdup (filename);
      if (!cur->info.filename)
	{
	  ++errors;
	  goto done;
	}
    }
  else
    {
      cur->info.filename = 0;
    }

  while (loader)
    {
      if (useloader && strcmp(loader->loader_name, useloader))
	{
	  loader = loader->next;
	  continue;
	}
      lt_user_data data = loader->dlloader_data;

      cur->module = loader->module_open (data, filename);

      if (cur->module != 0)
	{
	  break;
	}
      loader = loader->next;
    }

  if (!loader)
    {
      LT_DLFREE (cur->info.filename);
      ++errors;
      goto done;
    }

  cur->loader	= loader;
  LT_DLMUTEX_SETERROR (saved_error);

 done:
  LT_DLMUTEX_UNLOCK ();

  return errors;
}

static int
tryall_dlopen_module (handle, prefix, dirname, dlname)
     lt_dlhandle *handle;
     const char *prefix;
     const char *dirname;
     const char *dlname;
{
  int      error	= 0;
  char     *filename	= 0;
  size_t   filename_len	= 0;
  size_t   dirname_len	= LT_STRLEN (dirname);

  assert (handle);
  assert (dirname);
  assert (dlname);
#ifdef LT_DIRSEP_CHAR
  /* Only canonicalized names (i.e. with DIRSEP chars already converted)
     should make it into this function:  */
  assert (strchr (dirname, LT_DIRSEP_CHAR) == 0);
#endif

  if (dirname_len > 0)
    if (dirname[dirname_len -1] == '/')
      --dirname_len;
  filename_len = dirname_len + 1 + LT_STRLEN (dlname);

  /* Allocate memory, and combine DIRNAME and MODULENAME into it.
     The PREFIX (if any) is handled below.  */
  filename  = LT_EMALLOC (char, dirname_len + 1 + filename_len + 1);
  if (!filename)
    return 1;

  sprintf (filename, "%.*s/%s", (int) dirname_len, dirname, dlname);

  /* Now that we have combined DIRNAME and MODULENAME, if there is
     also a PREFIX to contend with, simply recurse with the arguments
     shuffled.  Otherwise, attempt to open FILENAME as a module.  */
  if (prefix)
    {
      error += tryall_dlopen_module (handle,
				     (const char *) 0, prefix, filename);
    }
  else if (tryall_dlopen (handle, filename, NULL) != 0)
    {
      ++error;
    }

  LT_DLFREE (filename);
  return error;
}

static int
find_module (handle, dir, libdir, dlname, old_name, installed)
     lt_dlhandle *handle;
     const char *dir;
     const char *libdir;
     const char *dlname;
     const char *old_name;
     int installed;
{
  /* Try to open the old library first; if it was dlpreopened,
     we want the preopened version of it, even if a dlopenable
     module is available.  */
  if (old_name && tryall_dlopen (handle, old_name, "dlpreload") == 0)
    {
      return 0;
    }

  /* Try to open the dynamic library.  */
  if (dlname)
    {
      /* try to open the installed module */
      if (installed && libdir)
	{
	  if (tryall_dlopen_module (handle,
				    (const char *) 0, libdir, dlname) == 0)
	    return 0;
	}

      /* try to open the not-installed module */
      if (!installed)
	{
	  if (tryall_dlopen_module (handle, dir, objdir, dlname) == 0)
	    return 0;
	}

      /* maybe it was moved to another directory */
      {
	  if (dir && (tryall_dlopen_module (handle,
				    (const char *) 0, dir, dlname) == 0))
	    return 0;
      }
    }

  return 1;
}


static int
canonicalize_path (path, pcanonical)
     const char *path;
     char **pcanonical;
{
  char *canonical = 0;

  assert (path && *path);
  assert (pcanonical);

  canonical = LT_EMALLOC (char, 1+ LT_STRLEN (path));
  if (!canonical)
    return 1;

  {
    size_t dest = 0;
    size_t src;
