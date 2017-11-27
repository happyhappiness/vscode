static lt_ptr
sys_shl_sym (loader_data, module, symbol)
     lt_user_data loader_data;
     lt_module module;
     const char *symbol;
{
  lt_ptr address = 0;

  /* sys_shl_open should never return a NULL module handle */
  if (module == (lt_module) 0)
  {
    LT_DLMUTEX_SETERROR (LT_DLSTRERROR (INVALID_HANDLE));
  }
  else if (!shl_findsym((shl_t*) &module, symbol, TYPE_UNDEFINED, &address))
    {
      if (!address)
	{
	  LT_DLMUTEX_SETERROR (LT_DLSTRERROR (SYMBOL_NOT_FOUND));
	}
    }

  return address;
}