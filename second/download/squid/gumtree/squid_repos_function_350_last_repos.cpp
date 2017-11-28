static lt_module
vm_open (lt_user_data loader_data LT__UNUSED, const char *filename,
         lt_dladvise advise LT__UNUSED)
{
  lt_module module = lt__strdup (filename);

  if (dld_link (filename) != 0)
    {
      LT__SETERROR (CANNOT_OPEN);
      FREE (module);
    }

  return module;
}