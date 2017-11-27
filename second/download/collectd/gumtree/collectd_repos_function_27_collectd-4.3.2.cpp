static int
sys_wll_close (loader_data, module)
     lt_user_data loader_data;
     lt_module module;
{
  int	      errors   = 0;

  if (FreeLibrary(module) == 0)
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (CANNOT_CLOSE));
      ++errors;
    }

  return errors;
}