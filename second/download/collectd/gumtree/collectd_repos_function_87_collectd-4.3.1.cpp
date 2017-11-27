int
lt_dlisresident	(handle)
     lt_dlhandle handle;
{
  if (!handle)
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (INVALID_HANDLE));
      return -1;
    }

  return LT_DLIS_RESIDENT (handle);
}