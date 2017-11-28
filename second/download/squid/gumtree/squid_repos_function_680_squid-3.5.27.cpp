static void *
vm_sym (lt_user_data loader_data LT__UNUSED, lt_module module LT__UNUSED,
	const char *name)
{
  void *address = dld_get_func (name);

  if (!address)
    {
      LT__SETERROR (SYMBOL_NOT_FOUND);
    }

  return address;
}