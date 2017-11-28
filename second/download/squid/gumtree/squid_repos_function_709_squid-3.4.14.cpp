static const mach_header *
lt__match_loadedlib (const char *name)
{
  const mach_header *mh	= 0;
  int i = _dyld_image_count();

  while (i > 0)
    {
      const char *id;

      --i;
      id = lt__header_get_instnam (_dyld_get_image_header (i));
      if (id && strneq (id, name))
	{
	  mh = _dyld_get_image_header (i);
	  break;
	}
    }

  return mh;
}