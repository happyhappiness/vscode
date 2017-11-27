static lt_module
sys_dyld_open (loader_data, filename)
     lt_user_data loader_data;
     const char *filename;
{
	lt_module   module   = 0;
	NSObjectFileImage ofi = 0;
	NSObjectFileImageReturnCode ofirc;

  	if (!filename)
  		return (lt_module)-1;
	ofirc = NSCreateObjectFileImageFromFile(filename, &ofi);
	switch (ofirc)
	{
		case NSObjectFileImageSuccess:
			module = NSLinkModule(ofi, filename,
						NSLINKMODULE_OPTION_RETURN_ON_ERROR
						 | NSLINKMODULE_OPTION_PRIVATE
						 | NSLINKMODULE_OPTION_BINDNOW);
			NSDestroyObjectFileImage(ofi);
			if (module)
				ltdl_NSMakePrivateModulePublic(module);
			break;
		case NSObjectFileImageInappropriateFile:
		    if (ltdl_NSIsSymbolNameDefinedInImage && ltdl_NSLookupSymbolInImage)
		    {
				module = (lt_module)ltdl_NSAddImage(filename, NSADDIMAGE_OPTION_RETURN_ON_ERROR);
				break;
			}
		default:
			LT_DLMUTEX_SETERROR (lt_int_dyld_error(LT_DLSTRERROR(CANNOT_OPEN)));
			return 0;
	}
	if (!module) LT_DLMUTEX_SETERROR (lt_int_dyld_error(LT_DLSTRERROR(CANNOT_OPEN)));
  return module;
}