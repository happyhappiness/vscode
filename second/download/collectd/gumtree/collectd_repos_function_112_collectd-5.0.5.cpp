static lt_module
vm_open (lt_user_data LT__UNUSED loader_data, const char *filename,
         lt_dladvise LT__UNUSED advise)
{
  static shl_t self = (shl_t) 0;
  lt_module module = shl_load (filename, LT_BIND_FLAGS, 0L);

  /* Since searching for a symbol against a NULL module handle will also
     look in everything else that was already loaded and exported with
     the -E compiler flag, we always cache a handle saved before any
     modules are loaded.  */
  if (!self)
    {
      void *address;
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
	  LT__SETERROR (CANNOT_OPEN);
	}
    }

  return module;
}