static const char* lt_int_dyld_lib_install_name(mh)
	const struct mach_header *mh;
{
/* NSAddImage is also used to get the loaded image, but it only works if the lib
   is installed, for uninstalled libs we need to check the install_names against
   each other. Note that this is still broken if DYLD_IMAGE_SUFFIX is set and a
   different lib was loaded as a result
*/
	int j;
	struct load_command *lc;
	unsigned long offset = sizeof(struct mach_header);
	const char* retStr=NULL;
	for (j = 0; j < mh->ncmds; j++)
	{
		lc = (struct load_command*)(((unsigned long)mh) + offset);
		if (LC_ID_DYLIB == lc->cmd)
		{
			retStr=(char*)(((struct dylib_command*)lc)->dylib.name.offset +
									(unsigned long)lc);
		}
		offset += lc->cmdsize;
	}
	return retStr;
}