static lt_ptr
presym_sym (loader_data, module, symbol)
     lt_user_data loader_data;
     lt_module module;
     const char *symbol;
{
  lt_dlsymlist *syms = (lt_dlsymlist*) module;

  ++syms;
  while (syms->address)
    {
      if (strcmp(syms->name, symbol) == 0)
	{
	  return syms->address;
	}

    ++syms;
  }

  LT_DLMUTEX_SETERROR (LT_DLSTRERROR (SYMBOL_NOT_FOUND));

  return 0;
}