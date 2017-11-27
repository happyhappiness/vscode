     At this stage, don't worry if the deplibs do not load correctly,
     they may already be statically linked into the loading application
     for instance.  There will be a more enlightening error message
     later on if the loaded module cannot resolve all of its symbols.  */
  if (depcount)
    {
      lt_dlhandle cur = handle;
      int	j = 0;

      cur->deplibs = MALLOC (lt_dlhandle, depcount);
      if (!cur->deplibs)
	goto cleanup_names;

      for (i = 0; i < depcount; ++i)
	{
	  cur->deplibs[j] = lt_dlopenext(names[depcount-1-i]);
	  if (cur->deplibs[j])
	    {
	      ++j;
	    }
	}

      cur->depcount	= j;	/* Number of successfully loaded deplibs */
      errors		= 0;
    }

 cleanup_names:
  for (i = 0; i < depcount; ++i)
    {
      FREE (names[i]);
    }

 cleanup:
  FREE (names);
  /* restore the old search path */
  if (save_search_path) {
    MEMREASSIGN (user_search_path, save_search_path);
  }

  return errors;
}
#endif /* defined(LTDL_DLOPEN_DEPLIBS) */

static int
unload_deplibs (lt_dlhandle handle)
{
  int i;
  int errors = 0;
  lt_dlhandle cur = handle;

  if (cur->depcount)
    {
      for (i = 0; i < cur->depcount; ++i)
	{
	  if (!LT_DLIS_RESIDENT (cur->deplibs[i]))
	    {
	      errors += lt_dlclose (cur->deplibs[i]);
	    }
	}
      FREE (cur->deplibs);
    }

  return errors;
}

static int
trim (char **dest, const char *str)
{
  /* remove the leading and trailing "'" from str
     and store the result in dest */
  const char *end   = strrchr (str, '\'');
  size_t len	    = LT_STRLEN (str);
  char *tmp;

  FREE (*dest);

  if (!end)
    return 1;

  if (len > 3 && str[0] == '\'')
    {
      tmp = MALLOC (char, end - str);
      if (!tmp)
	return 1;

      memcpy(tmp, &str[1], (end - str) - 1);
      tmp[(end - str) - 1] = LT_EOS_CHAR;
      *dest = tmp;
    }
  else
    {
      *dest = 0;
    }

  return 0;
}

/* Read the .la file FILE. */
static int
parse_dotla_file(FILE *file, char **dlname, char **libdir, char **deplibs,
    char **old_name, int *installed)
{
  int		errors = 0;
  size_t	line_len = LT_FILENAME_MAX;
  char *	line = MALLOC (char, line_len);

  if (!line)
    {
      LT__SETERROR (FILE_NOT_FOUND);
      return 1;
    }

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
	  line = REALLOC (char, line, line_len *2);
	  if (!line)
	    {
	      ++errors;
	      goto cleanup;
	    }
	  line[line_len * 2 - 2] = '\0';
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
	  errors += trim (dlname, &line[sizeof (STR_DLNAME) - 1]);
	}

#undef  STR_OLD_LIBRARY
#define STR_OLD_LIBRARY	"old_library="
      else if (strncmp (line, STR_OLD_LIBRARY,
	    sizeof (STR_OLD_LIBRARY) - 1) == 0)
	{
	  errors += trim (old_name, &line[sizeof (STR_OLD_LIBRARY) - 1]);
	}
#undef  STR_LIBDIR
#define STR_LIBDIR	"libdir="
      else if (strncmp (line, STR_LIBDIR, sizeof (STR_LIBDIR) - 1) == 0)
	{
	  errors += trim (libdir, &line[sizeof(STR_LIBDIR) - 1]);
	}

#undef  STR_DL_DEPLIBS
#define STR_DL_DEPLIBS	"dependency_libs="
      else if (strncmp (line, STR_DL_DEPLIBS,
	    sizeof (STR_DL_DEPLIBS) - 1) == 0)
	{
	  errors += trim (deplibs, &line[sizeof (STR_DL_DEPLIBS) - 1]);
	}
      else if (streq (line, "installed=yes\n"))
	{
	  *installed = 1;
	}
      else if (streq (line, "installed=no\n"))
	{
	  *installed = 0;
	}

#undef  STR_LIBRARY_NAMES
#define STR_LIBRARY_NAMES "library_names="
      else if (!*dlname && strncmp (line, STR_LIBRARY_NAMES,
	    sizeof (STR_LIBRARY_NAMES) - 1) == 0)
	{
	  char *last_libname;
	  errors += trim (dlname, &line[sizeof (STR_LIBRARY_NAMES) - 1]);
	  if (!errors
	      && *dlname
	      && (last_libname = strrchr (*dlname, ' ')) != 0)
	    {
	      last_libname = lt__strdup (last_libname + 1);
	      if (!last_libname)
		{
		  ++errors;
		  goto cleanup;
		}
	      MEMREASSIGN (*dlname, last_libname);
	    }
	}

      if (errors)
	break;
    }
cleanup:
  FREE (line);
  return errors;
}


/* Try to open FILENAME as a module. */
static int
try_dlopen (lt_dlhandle *phandle, const char *filename, const char *ext,
	    lt_dladvise advise)
{
  const char *	saved_error	= 0;
  char *	archive_name	= 0;
  char *	canonical	= 0;
  char *	base_name	= 0;
  char *	dir		= 0;
  char *	name		= 0;
  char *        attempt		= 0;
  int		errors		= 0;
  lt_dlhandle	newhandle;

  assert (phandle);
  assert (*phandle == 0);

#ifdef LT_DEBUG_LOADERS
  fprintf (stderr, "try_dlopen (%s, %s)\n",
	   filename ? filename : "(null)",
	   ext ? ext : "(null)");
#endif

  LT__GETERROR (saved_error);

  /* dlopen self? */
  if (!filename)
    {
      *phandle = (lt_dlhandle) lt__zalloc (sizeof (struct lt__handle));
      if (*phandle == 0)
	return 1;

      newhandle	= *phandle;

      /* lt_dlclose()ing yourself is very bad!  Disallow it.  */
      newhandle->info.is_resident = 1;

      if (tryall_dlopen (&newhandle, 0, advise, 0) != 0)
	{
	  FREE (*phandle);
	  return 1;
	}

      goto register_handle;
    }

  assert (filename && *filename);

  if (ext)
    {
      attempt = MALLOC (char, LT_STRLEN (filename) + LT_STRLEN (ext) + 1);
      if (!attempt)
	return 1;

      sprintf(attempt, "%s%s", filename, ext);
    }
  else
    {
      attempt = lt__strdup (filename);
      if (!attempt)
	return 1;
    }

  /* Doing this immediately allows internal functions to safely
     assume only canonicalized paths are passed.  */
  if (canonicalize_path (attempt, &canonical) != 0)
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

      dir = MALLOC (char, 1+ dirlen);
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
    MEMREASSIGN (base_name, canonical);

  assert (base_name && *base_name);

  ext = strrchr (base_name, '.');
  if (!ext)
    {
      ext = base_name + LT_STRLEN (base_name);
    }

  /* extract the module name from the file name */
  name = MALLOC (char, ext - base_name + 1);
  if (!name)
    {
      ++errors;
      goto cleanup;
    }

  /* canonicalize the module name */
  {
    int i;
    for (i = 0; i < ext - base_name; ++i)
      {
	if (isalnum ((unsigned char)(base_name[i])))
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

  /* Before trawling through the filesystem in search of a module,
     check whether we are opening a preloaded module.  */
  if (!dir)
    {
      const lt_dlvtable *vtable	= lt_dlloader_find ("lt_preopen");

      if (vtable)
	{
	  /* name + "." + libext + NULL */
	  archive_name = MALLOC (char, LT_STRLEN (name) + LT_STRLEN (libext) + 2);
	  *phandle = (lt_dlhandle) lt__zalloc (sizeof (struct lt__handle));

	  if ((*phandle == NULL) || (archive_name == NULL))
	    {
	      ++errors;
	      goto cleanup;
	    }
	  newhandle = *phandle;

	  /* Preloaded modules are always named according to their old
	     archive name.  */
	  sprintf (archive_name, "%s.%s", name, libext);

	  if (tryall_dlopen (&newhandle, archive_name, advise, vtable) == 0)
	    {
	      goto register_handle;
	    }

	  /* If we're still here, there was no matching preloaded module,
	     so put things back as we found them, and continue searching.  */
	  FREE (*phandle);
	  newhandle = NULL;
	}
    }

  /* If we are allowing only preloaded modules, and we didn't find
     anything yet, give up on the search here.  */
  if (advise && advise->try_preload_only)
    {
      goto cleanup;
    }

  /* Check whether we are opening a libtool module (.la extension).  */
  if (ext && streq (ext, archive_ext))
    {
      /* this seems to be a libtool module */
      FILE *	file	 = 0;
      char *	dlname	 = 0;
      char *	old_name = 0;
      char *	libdir	 = 0;
      char *	deplibs	 = 0;

      /* if we can't find the installed flag, it is probably an
	 installed libtool archive, produced with an old version
	 of libtool */
      int	installed = 1;

      /* Now try to open the .la file.  If there is no directory name
         component, try to find it first in user_search_path and then other
         prescribed paths.  Otherwise (or in any case if the module was not
         yet found) try opening just the module name as passed.  */
      if (!dir)
	{
	  const char *search_path = user_search_path;

	  if (search_path)
	    file = find_file (user_search_path, base_name, &dir);

	  if (!file)
	    {
	      search_path = getenv (LTDL_SEARCHPATH_VAR);
	      if (search_path)
		file = find_file (search_path, base_name, &dir);
	    }

#if defined(LT_MODULE_PATH_VAR)
	  if (!file)
	    {
	      search_path = getenv (LT_MODULE_PATH_VAR);
	      if (search_path)
		file = find_file (search_path, base_name, &dir);
	    }
#endif
#if defined(LT_DLSEARCH_PATH)
	  if (!file && *sys_dlsearch_path)
	    {
	      file = find_file (sys_dlsearch_path, base_name, &dir);
	    }
#endif
	}
      if (!file)
	{
	  file = fopen (attempt, LT_READTEXT_MODE);
	}

      /* If we didn't find the file by now, it really isn't there.  Set
	 the status flag, and bail out.  */
      if (!file)
	{
	  LT__SETERROR (FILE_NOT_FOUND);
	  ++errors;
	  goto cleanup;
	}

      /* read the .la file */
      if (parse_dotla_file(file, &dlname, &libdir, &deplibs,
	    &old_name, &installed) != 0)
	++errors;

      fclose (file);

      /* allocate the handle */
      *phandle = (lt_dlhandle) lt__zalloc (sizeof (struct lt__handle));
      if (*phandle == 0)
	++errors;

      if (errors)
	{
	  FREE (dlname);
	  FREE (old_name);
	  FREE (libdir);
	  FREE (deplibs);
	  FREE (*phandle);
	  goto cleanup;
	}

      assert (*phandle);

      if (load_deplibs (*phandle, deplibs) == 0)
	{
	  newhandle = *phandle;
	  /* find_module may replace newhandle */
	  if (find_module (&newhandle, dir, libdir, dlname, old_name,
			   installed, advise))
	    {
	      unload_deplibs (*phandle);
	      ++errors;
	    }
	}
      else
	{
	  ++errors;
	}

      FREE (dlname);
      FREE (old_name);
      FREE (libdir);
      FREE (deplibs);

      if (errors)
	{
	  FREE (*phandle);
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
      *phandle = (lt_dlhandle) lt__zalloc (sizeof (struct lt__handle));
      if (*phandle == 0)
	{
	  ++errors;
	  goto cleanup;
	}

      newhandle = *phandle;

      /* If the module has no directory name component, try to find it
	 first in user_search_path and then other prescribed paths.
	 Otherwise (or in any case if the module was not yet found) try
	 opening just the module name as passed.  */
      if ((dir || (!find_handle (user_search_path, base_name,
				 &newhandle, advise)
		   && !find_handle (getenv (LTDL_SEARCHPATH_VAR), base_name,
				    &newhandle, advise)
#if defined(LT_MODULE_PATH_VAR)
		   && !find_handle (getenv (LT_MODULE_PATH_VAR), base_name,
				    &newhandle, advise)
#endif
#if defined(LT_DLSEARCH_PATH)
		   && !find_handle (sys_dlsearch_path, base_name,
				    &newhandle, advise)
#endif
		   )))
	{
	  if (tryall_dlopen (&newhandle, attempt, advise, 0) != 0)
            {
              newhandle = NULL;
            }
	}

      if (!newhandle)
	{
	  FREE (*phandle);
	  ++errors;
	  goto cleanup;
	}
    }

 register_handle:
  MEMREASSIGN (*phandle, newhandle);

  if ((*phandle)->info.ref_count == 0)
    {
      (*phandle)->info.ref_count	= 1;
      MEMREASSIGN ((*phandle)->info.name, name);

      (*phandle)->next	= handles;
      handles		= *phandle;
    }

  LT__SETERRORSTR (saved_error);

 cleanup:
  FREE (dir);
  FREE (attempt);
  FREE (name);
  if (!canonical)		/* was MEMREASSIGNed */
    FREE (base_name);
  FREE (canonical);
  FREE (archive_name);

  return errors;
}


/* If the last error messge store was `FILE_NOT_FOUND', then return
   non-zero.  */
static int
file_not_found (void)
{
  const char *error = 0;

  LT__GETERROR (error);
  if (error == LT__STRERROR (FILE_NOT_FOUND))
    return 1;

  return 0;
}


/* Unless FILENAME already bears a suitable library extension, then
   return 0.  */
static int
has_library_ext (const char *filename)
{
  char *	ext     = 0;

  assert (filename);

  ext = strrchr (filename, '.');

  if (ext && ((streq (ext, archive_ext))
#if defined(LT_MODULE_EXT)
	     || (streq (ext, shlib_ext))
#endif
    ))
    {
      return 1;
    }

  return 0;
}


/* Initialise and configure a user lt_dladvise opaque object.  */

int
lt_dladvise_init (lt_dladvise *padvise)
{
  lt_dladvise advise = (lt_dladvise) lt__zalloc (sizeof (struct lt__advise));
  *padvise = advise;
  return (advise ? 0 : 1);
}

int
lt_dladvise_destroy (lt_dladvise *padvise)
{
  if (padvise)
    FREE(*padvise);
  return 0;
}

int
lt_dladvise_ext (lt_dladvise *padvise)
{
  assert (padvise && *padvise);
  (*padvise)->try_ext = 1;
  return 0;
}

int
lt_dladvise_resident (lt_dladvise *padvise)
{
  assert (padvise && *padvise);
  (*padvise)->is_resident = 1;
  return 0;
}

int
lt_dladvise_local (lt_dladvise *padvise)
{
  assert (padvise && *padvise);
  (*padvise)->is_symlocal = 1;
  return 0;
}

int
lt_dladvise_global (lt_dladvise *padvise)
{
  assert (padvise && *padvise);
  (*padvise)->is_symglobal = 1;
  return 0;
}

int
lt_dladvise_preload (lt_dladvise *padvise)
{
  assert (padvise && *padvise);
  (*padvise)->try_preload_only = 1;
  return 0;
}

/* Libtool-1.5.x interface for loading a new module named FILENAME.  */
lt_dlhandle
lt_dlopen (const char *filename)
{
  return lt_dlopenadvise (filename, NULL);
}


/* If FILENAME has an ARCHIVE_EXT or MODULE_EXT extension, try to
   open the FILENAME as passed.  Otherwise try appending ARCHIVE_EXT,
   and if a file is still not found try again with MODULE_EXT appended
   instead.  */
lt_dlhandle
lt_dlopenext (const char *filename)
{
  lt_dlhandle	handle	= 0;
  lt_dladvise	advise;

  if (!lt_dladvise_init (&advise) && !lt_dladvise_ext (&advise))
    handle = lt_dlopenadvise (filename, advise);

  lt_dladvise_destroy (&advise);
  return handle;
}


lt_dlhandle
lt_dlopenadvise (const char *filename, lt_dladvise advise)
{
  lt_dlhandle	handle	= 0;
  int		errors	= 0;
  const char *	saved_error	= 0;

  LT__GETERROR (saved_error);

  /* Can't have symbols hidden and visible at the same time!  */
  if (advise && advise->is_symlocal && advise->is_symglobal)
    {
      LT__SETERROR (CONFLICTING_FLAGS);
      return 0;
    }

  if (!filename
      || !advise
      || !advise->try_ext
      || has_library_ext (filename))
    {
      /* Just incase we missed a code path in try_dlopen() that reports
	 an error, but forgot to reset handle... */
      if (try_dlopen (&handle, filename, NULL, advise) != 0)
	return 0;

      return handle;
    }
  else if (filename && *filename)
    {

      /* First try appending ARCHIVE_EXT.  */
      errors += try_dlopen (&handle, filename, archive_ext, advise);

      /* If we found FILENAME, stop searching -- whether we were able to
	 load the file as a module or not.  If the file exists but loading
	 failed, it is better to return an error message here than to
	 report FILE_NOT_FOUND when the alternatives (foo.so etc) are not
	 in the module search path.  */
      if (handle || ((errors > 0) && !file_not_found ()))
	return handle;

#if defined(LT_MODULE_EXT)
      /* Try appending SHLIB_EXT.   */
      LT__SETERRORSTR (saved_error);
      errors = try_dlopen (&handle, filename, shlib_ext, advise);

      /* As before, if the file was found but loading failed, return now
	 with the current error message.  */
      if (handle || ((errors > 0) && !file_not_found ()))
	return handle;
#endif
    }

  /* Still here?  Then we really did fail to locate any of the file
     names we tried.  */
  LT__SETERROR (FILE_NOT_FOUND);
  return 0;
}


static int
lt_argz_insert (char **pargz, size_t *pargz_len, char *before,
		const char *entry)
{
  error_t error;

  /* Prior to Sep 8, 2005, newlib had a bug where argz_insert(pargz,
     pargz_len, NULL, entry) failed with EINVAL.  */
  if (before)
    error = argz_insert (pargz, pargz_len, before, entry);
  else
    error = argz_append (pargz, pargz_len, entry, 1 + strlen (entry));

  if (error)
    {
      switch (error)
	{
	case ENOMEM:
	  LT__SETERROR (NO_MEMORY);
	  break;
	default:
	  LT__SETERROR (UNKNOWN);
	  break;
	}
      return 1;
    }

  return 0;
}

static int
lt_argz_insertinorder (char **pargz, size_t *pargz_len, const char *entry)
{
  char *before = 0;

  assert (pargz);
  assert (pargz_len);
  assert (entry && *entry);
