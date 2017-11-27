int
lt_dlloader_remove (loader_name)
     const char *loader_name;
{
  lt_dlloader *place = lt_dlloader_find (loader_name);
  lt_dlhandle handle;
  int errors = 0;

  if (!place)
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (INVALID_LOADER));
      return 1;
    }

  LT_DLMUTEX_LOCK ();

  /* Fail if there are any open modules which use this loader. */
  for  (handle = handles; handle; handle = handle->next)
    {
      if (handle->loader == place)
	{
	  LT_DLMUTEX_SETERROR (LT_DLSTRERROR (REMOVE_LOADER));
	  ++errors;
	  goto done;
	}
    }

  if (place == loaders)
    {
      /* PLACE is the first loader in the list. */
      loaders = loaders->next;
    }
  else
    {
      /* Find the loader before the one being removed. */
      lt_dlloader *prev;
      for (prev = loaders; prev->next; prev = prev->next)
	{
	  if (!strcmp (prev->next->loader_name, loader_name))
	    {
	      break;
	    }
	}

      place = prev->next;
      prev->next = prev->next->next;
    }

  if (place->dlloader_exit)
    {
      errors = place->dlloader_exit (place->dlloader_data);
    }

  LT_DLFREE (place);

 done:
  LT_DLMUTEX_UNLOCK ();

  return errors;
}