static lt_module
sys_shl_open (loader_data, filename)
     lt_user_data loader_data;
     const char *filename;
{
  static shl_t self = (shl_t) 0;
  lt_module module = shl_load (filename, LT_BIND_FLAGS, 0L);

  /* Since searching for a symbol against a NULL module handle will also
     look in everything else that was already loaded and exported with
     the -E compiler flag, we always cache a handle saved before any
     modules are loaded.  */
  if (!self)
    {
      lt_ptr address;
      shl_findsym (&self, "main", TYPE_UNDEFINED, &address);
    }

  if (!filename)
    {
      module = self;
    }
  else
    {
      module = shl_load (filename, LT_BIND_FLAGS, 0L);

      if (!module)
	{
	  LT_DLMUTEX_SETERROR (LT_DLSTRERROR (CANNOT_OPEN));
	}
    }

  return module;
}