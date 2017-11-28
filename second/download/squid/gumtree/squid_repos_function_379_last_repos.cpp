static void *
vm_sym (lt_user_data loader_data LT__UNUSED, lt_module module, const char *name)
{
  lt_dlsymlist	       *symbol = (lt_dlsymlist*) module;

  if (symbol[1].name && STREQ (symbol[1].name, "@INIT@"))
    {
      symbol++;			/* Skip optional init entry. */
    }

  symbol +=2;			/* Skip header (originator then libname). */

  while (symbol->name)
    {
      if (STREQ (symbol->name, name))
	{
	  return symbol->address;
	}

    ++symbol;
  }

  LT__SETERROR (SYMBOL_NOT_FOUND);

  return 0;
}