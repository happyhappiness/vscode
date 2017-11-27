static int
foreach_dirinpath (search_path, base_name, func, data1, data2)
     const char *search_path;
     const char *base_name;
     foreach_callback_func *func;
     lt_ptr data1;
     lt_ptr data2;
{
  int	 result		= 0;
  int	 filenamesize	= 0;
  size_t lenbase	= LT_STRLEN (base_name);
  size_t argz_len	= 0;
  char *argz		= 0;
  char *filename	= 0;
  char *canonical	= 0;

  LT_DLMUTEX_LOCK ();

  if (!search_path || !*search_path)
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (FILE_NOT_FOUND));
      goto cleanup;
    }

  if (canonicalize_path (search_path, &canonical) != 0)
    goto cleanup;

  if (argzize_path (canonical, &argz, &argz_len) != 0)
    goto cleanup;

  {
    char *dir_name = 0;
    while ((dir_name = argz_next (argz, argz_len, dir_name)))
      {
	size_t lendir = LT_STRLEN (dir_name);

	if (lendir +1 +lenbase >= filenamesize)
	{
	  LT_DLFREE (filename);
	  filenamesize	= lendir +1 +lenbase +1; /* "/d" + '/' + "f" + '\0' */
	  filename	= LT_EMALLOC (char, filenamesize);
	  if (!filename)
	    goto cleanup;
	}

	assert (filenamesize > lendir);
	strcpy (filename, dir_name);

	if (base_name && *base_name)
	  {
	    if (filename[lendir -1] != '/')
	      filename[lendir++] = '/';
	    strcpy (filename +lendir, base_name);
	  }

	if ((result = (*func) (filename, data1, data2)))
	  {
	    break;
	  }
      }
  }

 cleanup:
  LT_DLFREE (argz);
  LT_DLFREE (canonical);
  LT_DLFREE (filename);

  LT_DLMUTEX_UNLOCK ();

  return result;
}