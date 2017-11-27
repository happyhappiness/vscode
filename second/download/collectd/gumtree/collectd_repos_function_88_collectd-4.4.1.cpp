const lt_dlinfo *
lt_dlgetinfo (handle)
     lt_dlhandle handle;
{
  if (!handle)
    {
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (INVALID_HANDLE));
      return 0;
    }

  return &(handle->info);
}