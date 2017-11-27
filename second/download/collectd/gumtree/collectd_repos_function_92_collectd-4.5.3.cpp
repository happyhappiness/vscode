lt_ptr
lt_dlcaller_get_data  (key, handle)
     lt_dlcaller_id key;
     lt_dlhandle handle;
{
  lt_ptr result = (lt_ptr) 0;

  /* This needs to be locked so that the caller data isn't updated by
     another thread part way through this function.  */
  LT_DLMUTEX_LOCK ();

  /* Locate the index of the element with a matching KEY.  */
  if (handle->caller_data)
    {
      int i;
      for (i = 0; handle->caller_data[i].key; ++i)
        {
          if (handle->caller_data[i].key == key)
            {
              result = handle->caller_data[i].data;
              break;
            }
        }
    }

  LT_DLMUTEX_UNLOCK ();

  return result;
}