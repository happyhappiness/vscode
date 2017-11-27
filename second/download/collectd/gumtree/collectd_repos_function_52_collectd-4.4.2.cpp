int
lt_dlpreload (preloaded)
     const lt_dlsymlist *preloaded;
{
  int errors = 0;

  if (preloaded)
    {
      errors = presym_add_symlist (preloaded);
    }
  else
    {
      presym_free_symlists();

      LT_DLMUTEX_LOCK ();
      if (default_preloaded_symbols)
	{
	  errors = lt_dlpreload (default_preloaded_symbols);
	}
      LT_DLMUTEX_UNLOCK ();
    }

  return errors;
}