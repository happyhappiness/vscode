static int
vl_init (lt_user_data loader_data LT__UNUSED)
{
  int errors = 0;

  preloaded_symlists = 0;
  if (default_preloaded_symbols)
    {
      errors = lt_dlpreload (default_preloaded_symbols);
    }

  return errors;
}