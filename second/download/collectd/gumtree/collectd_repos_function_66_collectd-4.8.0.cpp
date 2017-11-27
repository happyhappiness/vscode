static int
unload_deplibs (handle)
     lt_dlhandle handle;
{
  int i;
  int errors = 0;

  if (handle->depcount)
    {
      for (i = 0; i < handle->depcount; ++i)
	{
	  if (!LT_DLIS_RESIDENT (handle->deplibs[i]))
	    {
	      errors += lt_dlclose (handle->deplibs[i]);
	    }
	}
      LT_DLFREE (handle->deplibs);
    }

  return errors;
}