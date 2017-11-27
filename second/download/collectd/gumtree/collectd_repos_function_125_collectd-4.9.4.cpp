static NSSymbol
lt__linkedlib_symbol (const char *symname, const mach_header *mh)
{
  NSSymbol symbol = 0;

  if (lt__image_symbol && NSIsSymbolNameDefined (symname))
    {
      unsigned long offset = sizeof(mach_header);
      struct load_command *lc;
      int j;

      for (j = 0; j < mh->ncmds; j++)
	{
	  lc = (struct load_command*) (((unsigned long) mh) + offset);
	  if ((LC_LOAD_DYLIB == lc->cmd) || (LC_LOAD_WEAK_DYLIB == lc->cmd))
	    {
	      unsigned long base = ((dylib_command *) lc)->dylib.name.offset;
	      char *name = (char *) (base + (unsigned long) lc);
	      const mach_header *mh1 = lt__match_loadedlib (name);

	      if (!mh1)
		{
		  /* Maybe NSAddImage can find it */
		  mh1 = lt__addimage (name,
				      NSADDIMAGE_OPTION_RETURN_ONLY_IF_LOADED
				      | NSADDIMAGE_OPTION_WITH_SEARCHING
				      | NSADDIMAGE_OPTION_RETURN_ON_ERROR);
		}

	      if (mh1)
		{
		  symbol = lt__image_symbol (mh1, symname, LT__SYMLOOKUP_OPTS);
		  if (symbol)
		    break;
		}
	    }

	  offset += lc->cmdsize;
	}
    }

  return symbol;
}