static int
vl_init (lt_user_data loader_data)
{
  int errors = 0;

  if (! dyld_cannot_close)
    {
      if (!_dyld_present ())
	{
	  ++errors;
	}
      else
	{
	  (void) _dyld_func_lookup ("__dyld_NSAddImage",
				    (unsigned long*) &lt__addimage);
	  (void) _dyld_func_lookup ("__dyld_NSLookupSymbolInImage",
				    (unsigned long*)&lt__image_symbol);
	  (void) _dyld_func_lookup ("__dyld_NSIsSymbolNameDefinedInImage",
				    (unsigned long*) &lt__image_symbol_p);
	  (void) _dyld_func_lookup ("__dyld_NSMakePrivateModulePublic",
				    (unsigned long*) &lt__module_export);
	  dyld_cannot_close = lt_dladderror ("can't close a dylib");
	}
    }

  return errors;
}