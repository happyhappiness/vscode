static BOOL WINAPI
fallback_setthreaderrormode (DWORD mode, DWORD *oldmode)
{
  /* Prior to Windows 7, there was no way to set the thread local error
     mode, so set the process global error mode instead. */
  DWORD old = (DWORD) SetErrorMode (mode);
  if (oldmode)
    *oldmode = old;
  return TRUE;
}