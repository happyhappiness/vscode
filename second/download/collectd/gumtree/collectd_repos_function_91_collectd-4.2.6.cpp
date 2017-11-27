lt_ptr
lt_dlcaller_set_data (key, handle, data)
     lt_dlcaller_id key;
     lt_dlhandle handle;
     lt_ptr data;
{
  int n_elements = 0;
  lt_ptr stale = (lt_ptr) 0;
  int i;

  /* This needs to be locked so that the caller data can be updated
     simultaneously by different threads.  */
  LT_DLMUTEX_LOCK ();

  if (handle->caller_data)
    while (handle->caller_data[n_elements].key)
      ++n_elements;

  for (i = 0; i < n_elements; ++i)
    {
      if (handle->caller_data[i].key == key)
	{
	  stale = handle->caller_data[i].data;
	  break;
	}
    }

  /* Ensure that there is enough room in this handle's caller_data
     array to accept a new element (and an empty end marker).  */
  if (i == n_elements)
    {
      lt_caller_data *temp
	= LT_DLREALLOC (lt_caller_data, handle->caller_data, 2+ n_elements);

      if (!temp)
	{
	  stale = 0;
	  goto done;
	}

      handle->caller_data = temp;

      /* We only need this if we needed to allocate a new caller_data.  */
      handle->caller_data[i].key  = key;
      handle->caller_data[1+ i].key = 0;
    }

  handle->caller_data[i].data = data;

 done:
  LT_DLMUTEX_UNLOCK ();

  return stale;
}