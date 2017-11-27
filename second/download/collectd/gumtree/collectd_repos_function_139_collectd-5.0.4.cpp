int
lt_dlpreload_default (const lt_dlsymlist *preloaded)
{
  default_preloaded_symbols = preloaded;
  return 0;
}