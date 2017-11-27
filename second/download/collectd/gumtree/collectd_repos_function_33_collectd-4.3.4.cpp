static int
sys_dld_close (loader_data, module)
     lt_user_data loader_data;
     lt_module module;
{
  int errors = 0;

  if (dld_unlink_by_file ((char*)(module), 1) != 0)
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (CANNOT_CLOSE));
      ++errors;
    }
  else
    {
      LT_DLFREE (module);
    }

  return errors;
}