int
lt_dlclose (handle)
     lt_dlhandle handle;
{
  lt_dlhandle cur, last;
  int errors = 0;

  LT_DLMUTEX_LOCK ();

  /* check whether the handle is valid */
  last = cur = handles;
  while (cur && handle != cur)
    {
      last = cur;
      cur = cur->next;
    }

  if (!cur)
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (INVALID_HANDLE));
      ++errors;
      goto done;
    }

  handle->info.ref_count--;

  /* Note that even with resident modules, we must track the ref_count
     correctly incase the user decides to reset the residency flag
     later (even though the API makes no provision for that at the
     moment).  */
  if (handle->info.ref_count <= 0 && !LT_DLIS_RESIDENT (handle))
    {
      lt_user_data data = handle->loader->dlloader_data;

      if (handle != handles)
	{
	  last->next = handle->next;
	}
      else
	{
	  handles = handle->next;
	}

      errors += handle->loader->module_close (data, handle->module);
      errors += unload_deplibs(handle);

      /* It is up to the callers to free the data itself.  */
      LT_DLFREE (handle->caller_data);

      LT_DLFREE (handle->info.filename);
      LT_DLFREE (handle->info.name);
      LT_DLFREE (handle);

      goto done;
    }

  if (LT_DLIS_RESIDENT (handle))
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (CLOSE_RESIDENT_MODULE));
      ++errors;
    }

 done:
  LT_DLMUTEX_UNLOCK ();

  return errors;
}