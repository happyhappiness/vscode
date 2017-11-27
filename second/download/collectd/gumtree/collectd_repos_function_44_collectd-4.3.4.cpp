static int
presym_init (loader_data)
     lt_user_data loader_data;
{
  int errors = 0;

  LT_DLMUTEX_LOCK ();

  preloaded_symbols = 0;
  if (default_preloaded_symbols)
    {
      errors = lt_dlpreload (default_preloaded_symbols);
    }

  LT_DLMUTEX_UNLOCK ();

  return errors;
}