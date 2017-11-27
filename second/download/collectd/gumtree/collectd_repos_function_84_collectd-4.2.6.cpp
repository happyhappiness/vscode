int
lt_dlsetsearchpath (search_path)
     const char *search_path;
{
  int   errors	    = 0;

  LT_DLMUTEX_LOCK ();
  LT_DLFREE (user_search_path);
  LT_DLMUTEX_UNLOCK ();

  if (!search_path || !LT_STRLEN (search_path))
    {
      return errors;
    }

  LT_DLMUTEX_LOCK ();
  if (canonicalize_path (search_path, &user_search_path) != 0)
    ++errors;
  LT_DLMUTEX_UNLOCK ();

  return errors;
}