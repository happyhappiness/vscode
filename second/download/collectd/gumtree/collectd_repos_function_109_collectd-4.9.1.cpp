static void *
vm_sym (lt_user_data LT__UNUSED loader_data, lt_module LT__UNUSED module,
	const char *name)
{
  void *address = dld_get_func (name);

  if (!address)
    {
      LT__SETERROR (SYMBOL_NOT_FOUND);
    }

  return address;
}