int
lt_dlpreload (const lt_dlsymlist *preloaded)
{
  int errors = 0;

  if (preloaded)
    {
      errors = add_symlist (preloaded);
    }
  else
    {
      free_symlists();

      if (default_preloaded_symbols)
	{
	  errors = lt_dlpreload (default_preloaded_symbols);
	}
    }

  return errors;
}