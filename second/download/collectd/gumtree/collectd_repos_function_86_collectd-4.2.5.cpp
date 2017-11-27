int
lt_dlmakeresident (handle)
     lt_dlhandle handle;
{
  int errors = 0;

  if (!handle)
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (INVALID_HANDLE));
      ++errors;
    }
  else
    {
      LT_DLSET_FLAG (handle, LT_DLRESIDENT_FLAG);
    }

  return errors;
}