const char *
lt_dlgetsearchpath ()
{
  const char *saved_path;

  LT_DLMUTEX_LOCK ();
  saved_path = user_search_path;
  LT_DLMUTEX_UNLOCK ();

  return saved_path;
}