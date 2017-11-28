static void *
vm_sym (lt_user_data LT__UNUSED loader_data, lt_module module, const char *name)
{
  lt_dlsymlist	       *symbol = (lt_dlsymlist*) module;

  symbol +=2;			/* Skip header (originator then libname). */

  while (symbol->name)
    {
      if (streq (symbol->name, name))
	{
	  return symbol->address;
	}

    ++symbol;
  }

  LT__SETERROR (SYMBOL_NOT_FOUND);

  return 0;
}