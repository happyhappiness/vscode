int
lt_dlinsertsearchdir (before, search_dir)
     const char *before;
     const char *search_dir;
{
  int errors = 0;

  if (before)
    {
      LT_DLMUTEX_LOCK ();
      if ((before < user_search_path)
	  || (before >= user_search_path + LT_STRLEN (user_search_path)))
	{
	  LT_DLMUTEX_UNLOCK ();
	  LT_DLMUTEX_SETERROR (LT_DLSTRERROR (INVALID_POSITION));
	  return 1;
	}
      LT_DLMUTEX_UNLOCK ();
    }

  if (search_dir && *search_dir)
    {
      LT_DLMUTEX_LOCK ();
      if (lt_dlpath_insertdir (&user_search_path,
			       (char *) before, search_dir) != 0)
	{
	  ++errors;
	}
      LT_DLMUTEX_UNLOCK ();
    }

  return errors;
}