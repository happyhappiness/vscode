static lt_module
vm_open (lt_user_data loader_data, const char *filename,
         lt_dladvise advise LT__UNUSED)
{
  lt_module module = 0;
  NSObjectFileImage ofi = 0;

  if (!filename)
    {
      return (lt_module) -1;
    }

  switch (NSCreateObjectFileImageFromFile (filename, &ofi))
    {
    case NSObjectFileImageSuccess:
      module = NSLinkModule (ofi, filename, NSLINKMODULE_OPTION_RETURN_ON_ERROR
					    | NSLINKMODULE_OPTION_PRIVATE
					    | NSLINKMODULE_OPTION_BINDNOW);
      NSDestroyObjectFileImage (ofi);

      if (module)
	{
	  lt__module_export (module);
	}
      break;

    case NSObjectFileImageInappropriateFile:
      if (lt__image_symbol_p && lt__image_symbol)
	{
	  module = (lt_module) lt__addimage(filename,
					    NSADDIMAGE_OPTION_RETURN_ON_ERROR);
	}
      break;

    case NSObjectFileImageFailure:
    case NSObjectFileImageArch:
    case NSObjectFileImageFormat:
    case NSObjectFileImageAccess:
      /*NOWORK*/
      break;
    }

  if (!module)
    {
      DYLD__SETERROR (CANNOT_OPEN);
    }

  return module;
}