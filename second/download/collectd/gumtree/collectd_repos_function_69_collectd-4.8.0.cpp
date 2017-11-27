static int
try_dlopen (phandle, filename)
     lt_dlhandle *phandle;
     const char *filename;
{
  const char *	ext		= 0;
  const char *	saved_error	= 0;
  char *	canonical	= 0;
  char *	base_name	= 0;
  char *	dir		= 0;
  char *	name		= 0;
  int		errors		= 0;
  lt_dlhandle	newhandle;

  assert (phandle);
  assert (*phandle == 0);

  LT_DLMUTEX_GETERROR (saved_error);

  /* dlopen self? */
  if (!filename)
    {
      *phandle = (lt_dlhandle) LT_EMALLOC (struct lt_dlhandle_struct, 1);
      if (*phandle == 0)
	return 1;

      memset (*phandle, 0, sizeof(struct lt_dlhandle_struct));
      newhandle	= *phandle;

      /* lt_dlclose()ing yourself is very bad!  Disallow it.  */
      LT_DLSET_FLAG (*phandle, LT_DLRESIDENT_FLAG);

      if (tryall_dlopen (&newhandle, 0) != 0)
	{
	  LT_DLFREE (*phandle);
	  return 1;
	}

      goto register_handle;
    }

  assert (filename && *filename);

  /* Doing this immediately allows internal functions to safely
     assume only canonicalized paths are passed.  */
  if (canonicalize_path (filename, &canonical) != 0)
    {
      ++errors;
      goto cleanup;
    }

  /* If the canonical module name is a path (relative or absolute)
     then split it into a directory part and a name part.  */
  base_name = strrchr (canonical, '/');
  if (base_name)
    {
      size_t dirlen = (1+ base_name) - canonical;

      dir = LT_EMALLOC (char, 1+ dirlen);
      if (!dir)
	{
	  ++errors;
	  goto cleanup;
	}

      strncpy (dir, canonical, dirlen);
      dir[dirlen] = LT_EOS_CHAR;

      ++base_name;
    }
  else
    base_name = canonical;

  assert (base_name && *base_name);

  /* Check whether we are opening a libtool module (.la extension).  */
  ext = strrchr (base_name, '.');
  if (ext && strcmp (ext, archive_ext) == 0)
    {
      /* this seems to be a libtool module */
      FILE *	file	 = 0;
      char *	dlname	 = 0;
      char *	old_name = 0;
      char *	libdir	 = 0;
      char *	deplibs	 = 0;
      char *    line	 = 0;
      size_t	line_len;

      /* if we can't find the installed flag, it is probably an
	 installed libtool archive, produced with an old version
	 of libtool */
      int	installed = 1;

      /* extract the module name from the file name */
      name = LT_EMALLOC (char, ext - base_name + 1);
      if (!name)
	{
	  ++errors;
	  goto cleanup;
	}

      /* canonicalize the module name */
      {
        size_t i;
        for (i = 0; i < ext - base_name; ++i)
	  {
	    if (isalnum ((int)(base_name[i])))
	      {
	        name[i] = base_name[i];
	      }
	    else
	      {
	        name[i] = '_';
	      }
	  }
        name[ext - base_name] = LT_EOS_CHAR;
      }

      /* Now try to open the .la file.  If there is no directory name
         component, try to find it first in user_search_path and then other
         prescribed paths.  Otherwise (or in any case if the module was not
         yet found) try opening just the module name as passed.  */
      if (!dir)
	{
	  const char *search_path;

	  LT_DLMUTEX_LOCK ();
	  search_path = user_search_path;
	  if (search_path)
	    file = find_file (user_search_path, base_name, &dir);
	  LT_DLMUTEX_UNLOCK ();

	  if (!file)
	    {
	      search_path = getenv (LTDL_SEARCHPATH_VAR);
	      if (search_path)
		file = find_file (search_path, base_name, &dir);
	    }

#ifdef LTDL_SHLIBPATH_VAR
	  if (!file)
	    {
	      search_path = getenv (LTDL_SHLIBPATH_VAR);
	      if (search_path)
		file = find_file (search_path, base_name, &dir);
	    }
#endif
#ifdef LTDL_SYSSEARCHPATH
	  if (!file && *sys_search_path)
	    {
	      file = find_file (sys_search_path, base_name, &dir);
	    }
#endif
	}
      if (!file)
	{
	  file = fopen (filename, LT_READTEXT_MODE);
	}

      /* If we didn't find the file by now, it really isn't there.  Set
	 the status flag, and bail out.  */
      if (!file)
	{
	  LT_DLMUTEX_SETERROR (LT_DLSTRERROR (FILE_NOT_FOUND));
	  ++errors;
	  goto cleanup;
	}

      line_len = LT_FILENAME_MAX;
      line = LT_EMALLOC (char, line_len);
      if (!line)
	{
	  fclose (file);
	  ++errors;
	  goto cleanup;
	}

      /* read the .la file */
      while (!feof (file))
	{
	  line[line_len-2] = '\0';
	  if (!fgets (line, (int) line_len, file))
	    {
	      break;
	    }

	  /* Handle the case where we occasionally need to read a line
	     that is longer than the initial buffer size.
	     Behave even if the file contains NUL bytes due to corruption. */
	  while (line[line_len-2] != '\0' && line[line_len-2] != '\n' && !feof (file))
	    {
	      line = LT_DLREALLOC (char, line, line_len *2);
	      line[line_len*2 - 2] = '\0';
	      if (!fgets (&line[line_len -1], (int) line_len +1, file))
		{
		  break;
		}
	      line_len *= 2;
	    }

	  if (line[0] == '\n' || line[0] == '#')
	    {
	      continue;
	    }

#undef  STR_DLNAME
#define STR_DLNAME	"dlname="
	  if (strncmp (line, STR_DLNAME, sizeof (STR_DLNAME) - 1) == 0)
	    {
	      errors += trim (&dlname, &line[sizeof (STR_DLNAME) - 1]);
	    }

#undef  STR_OLD_LIBRARY
#define STR_OLD_LIBRARY	"old_library="
	  else if (strncmp (line, STR_OLD_LIBRARY,
			    sizeof (STR_OLD_LIBRARY) - 1) == 0)
	    {
	      errors += trim (&old_name, &line[sizeof (STR_OLD_LIBRARY) - 1]);
	    }
#undef  STR_LIBDIR
#define STR_LIBDIR	"libdir="
	  else if (strncmp (line, STR_LIBDIR, sizeof (STR_LIBDIR) - 1) == 0)
	    {
	      errors += trim (&libdir, &line[sizeof(STR_LIBDIR) - 1]);
	    }

#undef  STR_DL_DEPLIBS
#define STR_DL_DEPLIBS	"dependency_libs="
	  else if (strncmp (line, STR_DL_DEPLIBS,
			    sizeof (STR_DL_DEPLIBS) - 1) == 0)
	    {
	      errors += trim (&deplibs, &line[sizeof (STR_DL_DEPLIBS) - 1]);
	    }
	  else if (strcmp (line, "installed=yes\n") == 0)
	    {
	      installed = 1;
	    }
	  else if (strcmp (line, "installed=no\n") == 0)
	    {
	      installed = 0;
	    }

#undef  STR_LIBRARY_NAMES
#define STR_LIBRARY_NAMES "library_names="
	  else if (! dlname && strncmp (line, STR_LIBRARY_NAMES,
					sizeof (STR_LIBRARY_NAMES) - 1) == 0)
	    {
	      char *last_libname;
	      errors += trim (&dlname, &line[sizeof (STR_LIBRARY_NAMES) - 1]);
	      if (!errors
		  && dlname
		  && (last_libname = strrchr (dlname, ' ')) != 0)
		{
		  last_libname = lt_estrdup (last_libname + 1);
		  if (!last_libname)
		    {
		      ++errors;
		      goto cleanup;
		    }
		  LT_DLMEM_REASSIGN (dlname, last_libname);
		}
	    }

	  if (errors)
	    break;
	}

      fclose (file);
      LT_DLFREE (line);

      /* allocate the handle */
      *phandle = (lt_dlhandle) LT_EMALLOC (struct lt_dlhandle_struct, 1);
      if (*phandle == 0)
	++errors;

      if (errors)
	{
	  free_vars (dlname, old_name, libdir, deplibs);
	  LT_DLFREE (*phandle);
	  goto cleanup;
	}

      assert (*phandle);

      memset (*phandle, 0, sizeof(struct lt_dlhandle_struct));
      if (load_deplibs (*phandle, deplibs) == 0)
	{
	  newhandle = *phandle;
	  /* find_module may replace newhandle */
	  if (find_module (&newhandle, dir, libdir, dlname, old_name, installed))
	    {
	      unload_deplibs (*phandle);
	      ++errors;
	    }
	}
      else
	{
	  ++errors;
	}

      free_vars (dlname, old_name, libdir, deplibs);
      if (errors)
	{
	  LT_DLFREE (*phandle);
	  goto cleanup;
	}

      if (*phandle != newhandle)
	{
	  unload_deplibs (*phandle);
	}
    }
  else
    {
      /* not a libtool module */
      *phandle = (lt_dlhandle) LT_EMALLOC (struct lt_dlhandle_struct, 1);
      if (*phandle == 0)
	{
	  ++errors;
	  goto cleanup;
	}

      memset (*phandle, 0, sizeof (struct lt_dlhandle_struct));
      newhandle = *phandle;

      /* If the module has no directory name component, try to find it
	 first in user_search_path and then other prescribed paths.
	 Otherwise (or in any case if the module was not yet found) try
	 opening just the module name as passed.  */
      if ((dir || (!find_handle (user_search_path, base_name, &newhandle)
		   && !find_handle (getenv (LTDL_SEARCHPATH_VAR), base_name,
				    &newhandle)
#ifdef LTDL_SHLIBPATH_VAR
		   && !find_handle (getenv (LTDL_SHLIBPATH_VAR), base_name,
				    &newhandle)
#endif
#ifdef LTDL_SYSSEARCHPATH
		   && !find_handle (sys_search_path, base_name, &newhandle)
#endif
		   )))
	{
          if (tryall_dlopen (&newhandle, filename) != 0)
            {
              newhandle = NULL;
            }
	}

      if (!newhandle)
	{
	  LT_DLFREE (*phandle);
	  ++errors;
	  goto cleanup;
	}
    }

 register_handle:
  LT_DLMEM_REASSIGN (*phandle, newhandle);

  if ((*phandle)->info.ref_count == 0)
    {
      (*phandle)->info.ref_count	= 1;
      LT_DLMEM_REASSIGN ((*phandle)->info.name, name);

      LT_DLMUTEX_LOCK ();
      (*phandle)->next		= handles;
      handles			= *phandle;
      LT_DLMUTEX_UNLOCK ();
    }

  LT_DLMUTEX_SETERROR (saved_error);

 cleanup:
  LT_DLFREE (dir);
  LT_DLFREE (name);
  LT_DLFREE (canonical);

  return errors;
}