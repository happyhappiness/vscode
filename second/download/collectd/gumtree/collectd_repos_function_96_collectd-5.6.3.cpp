lt_dlvtable *
lt_dlloader_remove (const char *name)
{
  const lt_dlvtable *	vtable	= lt_dlloader_find (name);
  static const char	id_string[] = "lt_dlloader_remove";
  lt_dlinterface_id	iface;
  lt_dlhandle		handle = 0;
  int			in_use = 0;
  int			in_use_by_resident = 0;

  if (!vtable)
    {
      LT__SETERROR (INVALID_LOADER);
      return 0;
    }

  /* Fail if there are any open modules which use this loader.  */
  iface = lt_dlinterface_register (id_string, NULL);
  while ((handle = lt_dlhandle_iterate (iface, handle)))
    {
      lt_dlhandle cur = handle;
      if (cur->vtable == vtable)
	{
	  in_use = 1;
	  if (lt_dlisresident (handle))
	    in_use_by_resident = 1;
	}
    }
  lt_dlinterface_free (iface);
  if (in_use)
    {
      if (!in_use_by_resident)
	LT__SETERROR (REMOVE_LOADER);
      return 0;
    }

  /* Call the loader finalisation function.  */
  if (vtable && vtable->dlloader_exit)
    {
      if ((*vtable->dlloader_exit) (vtable->dlloader_data) != 0)
	{
	  /* If there is an exit function, and it returns non-zero
	     then it must set an error, and we will not remove it
	     from the list.  */
	  return 0;
	}
    }

  /* If we got this far, remove the loader from our global list.  */
  return (lt_dlvtable *)
      slist_unbox ((SList *) slist_remove (&loaders, loader_callback, (void *) name));
}