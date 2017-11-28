static void *
vm_sym (lt_user_data loader_data LT__UNUSED, lt_module module, const char *name)
{
  void *address = (void *) GetProcAddress ((HMODULE) module, name);

  if (!address)
    {
      LOADLIB_SETERROR (SYMBOL_NOT_FOUND);
    }

  return address;
}