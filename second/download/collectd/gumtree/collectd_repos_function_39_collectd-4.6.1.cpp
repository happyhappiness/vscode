static NSSymbol
lt_int_dyld_NSlookupSymbolInLinkedLibs(symbol,mh)
	const char *symbol;
	const struct mach_header *mh;
{
	/* Safe to assume our mh is good */
	int j;
	struct load_command *lc;
	unsigned long offset = sizeof(struct mach_header);
	NSSymbol retSym = 0;
	const struct mach_header *mh1;
	if ((ltdl_NSLookupSymbolInImage) && NSIsSymbolNameDefined(symbol) )
	{
		for (j = 0; j < mh->ncmds; j++)
		{
			lc = (struct load_command*)(((unsigned long)mh) + offset);
			if ((LC_LOAD_DYLIB == lc->cmd) || (LC_LOAD_WEAK_DYLIB == lc->cmd))
			{
				mh1=lt_int_dyld_match_loaded_lib_by_install_name((char*)(((struct dylib_command*)lc)->dylib.name.offset +
										(unsigned long)lc));
				if (!mh1)
				{
					/* Maybe NSAddImage can find it */
					mh1=ltdl_NSAddImage((char*)(((struct dylib_command*)lc)->dylib.name.offset +
										(unsigned long)lc),
										NSADDIMAGE_OPTION_RETURN_ONLY_IF_LOADED +
										NSADDIMAGE_OPTION_WITH_SEARCHING +
										NSADDIMAGE_OPTION_RETURN_ON_ERROR );
				}
				if (mh1)
				{
					retSym = ltdl_NSLookupSymbolInImage(mh1,
											symbol,
											NSLOOKUPSYMBOLINIMAGE_OPTION_BIND_NOW
											| NSLOOKUPSYMBOLINIMAGE_OPTION_RETURN_ON_ERROR
											);
					if (retSym) break;
				}
			}
			offset += lc->cmdsize;
		}
	}
	return retSym;
}