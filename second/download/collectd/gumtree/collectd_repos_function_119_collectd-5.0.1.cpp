static int
vm_close (lt_user_data loader_data, lt_module module)
{
  int errors = 0;

  if (module != (lt_module) -1)
    {
      const mach_header *mh = (const mach_header *) module;
      int flags = 0;
      if (mh->magic == LT__MAGIC)
	{
	  lt_dlseterror (dyld_cannot_close);
	  ++errors;
	}
      else
	{
	  /* Currently, if a module contains c++ static destructors and it
	     is unloaded, we get a segfault in atexit(), due to compiler and
	     dynamic loader differences of opinion, this works around that.  */
	  if ((const struct section *) NULL !=
	      getsectbynamefromheader (lt__nsmodule_get_header (module),
				       "__DATA", "__mod_term_func"))
	    {
	      flags |= NSUNLINKMODULE_OPTION_KEEP_MEMORY_MAPPED;
	    }
#if defined(__ppc__)
	  flags |= NSUNLINKMODULE_OPTION_RESET_LAZY_REFERENCES;
#endif
	  if (!NSUnLinkModule (module, flags))
	    {
	      DYLD__SETERROR (CANNOT_CLOSE);
	      ++errors;
	    }
	}
    }

  return errors;
}