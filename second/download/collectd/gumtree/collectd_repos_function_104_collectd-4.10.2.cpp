static void *
vm_sym (lt_user_data LT__UNUSED loader_data, lt_module module, const char *name)
{
  void *address = (void *) GetProcAddress ((HMODULE) module, name);

  if (!address)
    {
      LT__SETERROR (SYMBOL_NOT_FOUND);
    }

  return address;
}