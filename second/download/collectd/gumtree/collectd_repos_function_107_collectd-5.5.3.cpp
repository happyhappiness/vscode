static DWORD WINAPI
fallback_getthreaderrormode (void)
{
  /* Prior to Windows Vista, the only way to get the current error
     mode was to set a new one. In our case, we are setting a new
     error mode right after "getting" it while ignoring the error
     mode in effect when setting the new error mode, so that's
     fairly ok. */
  return (DWORD) SetErrorMode (SEM_FAILCRITICALERRORS);
}