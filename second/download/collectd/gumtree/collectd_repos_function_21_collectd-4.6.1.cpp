static int
sys_dl_close (loader_data, module)
     lt_user_data loader_data;
     lt_module module;
{
  int errors = 0;

  if (dlclose (module) != 0)
    {
      LT_DLMUTEX_SETERROR (DLERROR (CANNOT_CLOSE));
      ++errors;
    }

  return errors;
}