int
lt_dlpreload_default (preloaded)
     const lt_dlsymlist *preloaded;
{
  LT_DLMUTEX_LOCK ();
  default_preloaded_symbols = preloaded;
  LT_DLMUTEX_UNLOCK ();
  return 0;
}