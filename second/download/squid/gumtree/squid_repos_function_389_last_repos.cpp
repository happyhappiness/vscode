static void *
vm_sym (lt_user_data loader_data LT__UNUSED, lt_module module, const char *name)
{
  void *address = dlsym (module, name);

  if (!address)
    {
      DL__SETERROR (SYMBOL_NOT_FOUND);
    }

  return address;
}