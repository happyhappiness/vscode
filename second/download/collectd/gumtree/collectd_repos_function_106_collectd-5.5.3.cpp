static DWORD WINAPI
wrap_getthreaderrormode (void)
{
  HMODULE kernel32 = GetModuleHandleA ("kernel32.dll");
  getthreaderrormode
    = (getthreaderrormode_type *) GetProcAddress (kernel32,
						  "GetThreadErrorMode");
  if (!getthreaderrormode)
    getthreaderrormode
      = (getthreaderrormode_type *) GetProcAddress (kernel32,
						    "GetErrorMode");
  if (!getthreaderrormode)
    getthreaderrormode = fallback_getthreaderrormode;
  return getthreaderrormode ();
}