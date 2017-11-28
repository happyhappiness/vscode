static BOOL WINAPI
wrap_setthreaderrormode (DWORD mode, DWORD *oldmode)
{
  HMODULE kernel32 = GetModuleHandleA ("kernel32.dll");
  setthreaderrormode
    = (setthreaderrormode_type *) GetProcAddress (kernel32,
						  "SetThreadErrorMode");
  if (!setthreaderrormode)
    setthreaderrormode = fallback_setthreaderrormode;
  return setthreaderrormode (mode, oldmode);
}