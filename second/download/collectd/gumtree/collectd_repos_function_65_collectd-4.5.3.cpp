static int
load_deplibs (handle, deplibs)
     lt_dlhandle handle;
     char *deplibs;
{
#if LTDL_DLOPEN_DEPLIBS
  char	*p, *save_search_path = 0;
  int   depcount = 0;
  int	i;
  char	**names = 0;
#endif
  int	errors = 0;

  handle->depcount = 0;

#if LTDL_DLOPEN_DEPLIBS
  if (!deplibs)
    {
      return errors;
    }
  ++errors;

  LT_DLMUTEX_LOCK ();
  if (user_search_path)
    {
      save_search_path = lt_estrdup (user_search_path);
      if (!save_search_path)
	goto cleanup;
    }

  /* extract search paths and count deplibs */
  p = deplibs;
  while (*p)
    {
      if (!isspace ((int) *p))
	{
	  char *end = p+1;
	  while (*end && !isspace((int) *end))
	    {
	      ++end;
	    }

	  if (strncmp(p, "-L", 2) == 0 || strncmp(p, "-R", 2) == 0)
	    {
	      char save = *end;
	      *end = 0; /* set a temporary string terminator */
	      if (lt_dladdsearchdir(p+2))
		{
		  goto cleanup;
		}
	      *end = save;
	    }
	  else
	    {
	      ++depcount;
	    }

	  p = end;
	}
      else
	{
	  ++p;
	}
    }

  if (!depcount)
    {
      errors = 0;
      goto cleanup;
    }

  names = LT_EMALLOC (char *, depcount * sizeof (char*));
  if (!names)
    goto cleanup;

  /* now only extract the actual deplibs */
  depcount = 0;
  p = deplibs;
  while (*p)
    {
      if (isspace ((int) *p))
	{
	  ++p;
	}
      else
	{
	  char *end = p+1;
	  while (*end && !isspace ((int) *end))
	    {
	      ++end;
	    }

	  if (strncmp(p, "-L", 2) != 0 && strncmp(p, "-R", 2) != 0)
	    {
	      char *name;
	      char save = *end;
	      *end = 0; /* set a temporary string terminator */
	      if (strncmp(p, "-l", 2) == 0)
		{
		  size_t name_len = 3+ /* "lib" */ LT_STRLEN (p + 2);
		  name = LT_EMALLOC (char, 1+ name_len);
		  if (name)
		    sprintf (name, "lib%s", p+2);
		}
	      else
		name = lt_estrdup(p);

	      if (!name)
		goto cleanup_names;

	      names[depcount++] = name;
	      *end = save;
	    }
	  p = end;
	}
    }

  /* load the deplibs (in reverse order)
     At this stage, don't worry if the deplibs do not load correctly,
     they may already be statically linked into the loading application
     for instance.  There will be a more enlightening error message
     later on if the loaded module cannot resolve all of its symbols.  */
  if (depcount)
    {
      int	j = 0;

      handle->deplibs = (lt_dlhandle*) LT_EMALLOC (lt_dlhandle *, depcount);
      if (!handle->deplibs)
	goto cleanup_names;

      for (i = 0; i < depcount; ++i)
	{
	  handle->deplibs[j] = lt_dlopenext(names[depcount-1-i]);
	  if (handle->deplibs[j])
	    {
	      ++j;
	    }
	}

      handle->depcount	= j;	/* Number of successfully loaded deplibs */
      errors		= 0;
    }

 cleanup_names:
  for (i = 0; i < depcount; ++i)
    {
      LT_DLFREE (names[i]);
    }

 cleanup:
  LT_DLFREE (names);
  /* restore the old search path */
  if (user_search_path) {
    LT_DLFREE (user_search_path);
    user_search_path = save_search_path;
  }
  LT_DLMUTEX_UNLOCK ();

#endif

  return errors;
}