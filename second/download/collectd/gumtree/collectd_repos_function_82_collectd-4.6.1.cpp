int
lt_dladdsearchdir (search_dir)
     const char *search_dir;
{
  int errors = 0;

  if (search_dir && *search_dir)
    {
      LT_DLMUTEX_LOCK ();
      if (lt_dlpath_insertdir (&user_search_path, 0, search_dir) != 0)
	++errors;
      LT_DLMUTEX_UNLOCK ();
    }

  return errors;
}