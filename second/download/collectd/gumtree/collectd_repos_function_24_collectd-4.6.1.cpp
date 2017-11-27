static int
sys_shl_close (loader_data, module)
     lt_user_data loader_data;
     lt_module module;
{
  int errors = 0;

  if (module && (shl_unload ((shl_t) (module)) != 0))
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (CANNOT_CLOSE));
      ++errors;
    }

  return errors;
}