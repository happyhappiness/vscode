static const char *
lt__header_get_instnam (const mach_header *mh)
{
  unsigned long offset = sizeof(mach_header);
  const char* result   = 0;
  int j;

  for (j = 0; j < mh->ncmds; j++)
    {
      struct load_command *lc;

      lc = (struct load_command*) (((unsigned long) mh) + offset);
      if (LC_ID_DYLIB == lc->cmd)
	{
	  result=(char*)(((dylib_command*) lc)->dylib.name.offset +
			 (unsigned long) lc);
	}
      offset += lc->cmdsize;
    }

  return result;
}