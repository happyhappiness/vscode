static lt_ptr
sys_dyld_sym (loader_data, module, symbol)
     lt_user_data loader_data;
     lt_module module;
     const char *symbol;
{
	lt_ptr address = 0;
  	NSSymbol *nssym = 0;
  	void *unused;
  	const struct mach_header *mh=NULL;
  	char saveError[256] = "Symbol not found";
  	if (module == (lt_module)-1)
  	{
  		_dyld_lookup_and_bind(symbol,(unsigned long*)&address,&unused);
  		return address;
  	}
#ifdef __BIG_ENDIAN__
  	if (((struct mach_header *)module)->magic == MH_MAGIC)
#else
    if (((struct mach_header *)module)->magic == MH_CIGAM)
#endif
  	{
  	    if (ltdl_NSIsSymbolNameDefinedInImage && ltdl_NSLookupSymbolInImage)
  	    {
  	    	mh=module;
			if (ltdl_NSIsSymbolNameDefinedInImage((struct mach_header*)module,symbol))
			{
				nssym = ltdl_NSLookupSymbolInImage((struct mach_header*)module,
											symbol,
											NSLOOKUPSYMBOLINIMAGE_OPTION_BIND_NOW
											| NSLOOKUPSYMBOLINIMAGE_OPTION_RETURN_ON_ERROR
											);
			}
	    }

  	}
  else {
	nssym = NSLookupSymbolInModule(module, symbol);
	}
	if (!nssym)
	{
		strncpy(saveError, lt_int_dyld_error(LT_DLSTRERROR(SYMBOL_NOT_FOUND)), 255);
		saveError[255] = 0;
		if (!mh) mh=lt_int_dyld_get_mach_header_from_nsmodule(module);
		nssym = lt_int_dyld_NSlookupSymbolInLinkedLibs(symbol,mh);
	}
	if (!nssym)
	{
		LT_DLMUTEX_SETERROR (saveError);
		return NULL;
	}
	return NSAddressOfSymbol(nssym);
}