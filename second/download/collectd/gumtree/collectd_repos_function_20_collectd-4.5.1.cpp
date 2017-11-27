static lt_module
sys_dl_open (loader_data, filename)
     lt_user_data loader_data;
     const char *filename;
{
  lt_module   module   = dlopen (filename, LT_LAZY_OR_NOW);

  if (!module)
    {
      LT_DLMUTEX_SETERROR (DLERROR (CANNOT_OPEN));
    }

  return module;
}