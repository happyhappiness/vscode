static lt_module
sys_dld_open (loader_data, filename)
     lt_user_data loader_data;
     const char *filename;
{
  lt_module module = strdup (filename);

  if (dld_link (filename) != 0)
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (CANNOT_OPEN));
      LT_DLFREE (module);
      module = 0;
    }

  return module;
}