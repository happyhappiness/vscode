static void *
vm_sym (lt_user_data loader_data, lt_module module, const char *name)
{
  NSSymbol *nssym = 0;
  const mach_header *mh = (const mach_header *) module;
  char saveError[256] = "Symbol not found";

  if (module == (lt_module) -1)
    {
      void *address, *unused;
      _dyld_lookup_and_bind (name, (unsigned long*) &address, &unused);
      return address;
    }

  if (mh->magic == LT__MAGIC)
    {
      if (lt__image_symbol_p && lt__image_symbol)
	{
	  if (lt__image_symbol_p (mh, name))
	    {
	      nssym = lt__image_symbol (mh, name, LT__SYMLOOKUP_OPTS);
	    }
	}

    }
  else
    {
      nssym = NSLookupSymbolInModule (module, name);
    }

  if (!nssym)
    {
      strncpy (saveError, dylderror (LT__STRERROR (SYMBOL_NOT_FOUND)), 255);
      saveError[255] = 0;
      if (!mh)
	{
	  mh = (mach_header *)lt__nsmodule_get_header (module);
	}
      nssym = lt__linkedlib_symbol (name, mh);
    }

  if (!nssym)
    {
      LT__SETERRORSTR (saveError);
    }

  return nssym ? NSAddressOfSymbol (nssym) : 0;
}