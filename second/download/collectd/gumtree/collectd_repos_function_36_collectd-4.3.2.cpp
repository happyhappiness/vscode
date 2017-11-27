static const struct mach_header *
lt_int_dyld_get_mach_header_from_nsmodule(module)
	NSModule module;
{
/* There should probably be an apple dyld api for this */
	int i=_dyld_image_count();
	int j;
	const char *modname=NSNameOfModule(module);
	const struct mach_header *mh=NULL;
	if (!modname) return NULL;
	for (j = 0; j < i; j++)
	{
		if (!strcmp(_dyld_get_image_name(j),modname))
		{
			mh=_dyld_get_image_header(j);
			break;
		}
	}
	return mh;
}