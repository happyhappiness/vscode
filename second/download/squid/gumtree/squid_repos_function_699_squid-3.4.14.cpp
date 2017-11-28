static void *
vm_sym (lt_user_data LT__UNUSED loader_data, lt_module module, const char *name)
{
  void *address = 0;

  /* sys_shl_open should never return a NULL module handle */
  if (module == (lt_module) 0)
  {
    LT__SETERROR (INVALID_HANDLE);
  }
  else if (!shl_findsym((shl_t*) &module, name, TYPE_UNDEFINED, &address))
    {
      if (!address)
	{
	  LT__SETERROR (SYMBOL_NOT_FOUND);
	}
    }

  return address;
}