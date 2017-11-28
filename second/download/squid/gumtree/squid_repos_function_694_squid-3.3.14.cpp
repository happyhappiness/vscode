static const mach_header *
lt__nsmodule_get_header (NSModule module)
{
  int i = _dyld_image_count();
  const char *modname = NSNameOfModule (module);
  const mach_header *mh = 0;

  if (!modname)
    return NULL;

  while (i > 0)
    {
      --i;
      if (strneq (_dyld_get_image_name (i), modname))
	{
	  mh = _dyld_get_image_header (i);
	  break;
	}
    }

  return mh;
}