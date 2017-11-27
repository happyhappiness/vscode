static int
tryall_dlopen (handle, filename)
     lt_dlhandle *handle;
     const char *filename;
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