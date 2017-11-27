static lt_module
vm_open (lt_user_data LT__UNUSED loader_data, const char *filename,
         lt_dladvise LT__UNUSED advise)
{
  lt_module module = lt__strdup (filename);

  if (dld_link (filename) != 0)
    {
      LT__SETERROR (CANNOT_OPEN);
      FREE (module);
    }

  return module;
}