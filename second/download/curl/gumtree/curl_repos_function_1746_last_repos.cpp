HMODULE Curl_load_library(LPCTSTR filename)
{
  HMODULE hModule = NULL;
  LOADLIBRARYEX_FN pLoadLibraryEx = NULL;

  /* Get a handle to kernel32 so we can access it's functions at runtime */
  HMODULE hKernel32 = GetModuleHandle(TEXT("kernel32"));
  if(!hKernel32)
    return NULL;

  /* Attempt to find LoadLibraryEx() which is only available on Windows 2000
     and above */
  pLoadLibraryEx = (LOADLIBRARYEX_FN) GetProcAddress(hKernel32, LOADLIBARYEX);

  /* Detect if there's already a path in the filename and load the library if
     there is. Note: Both back slashes and forward slashes have been supported
     since the earlier days of DOS at an API level although they are not
     supported by command prompt */
  if(_tcspbrk(filename, TEXT("\\/"))) {
    /** !checksrc! disable BANNEDFUNC 1 **/
    hModule = pLoadLibraryEx ?
      pLoadLibraryEx(filename, NULL, LOAD_WITH_ALTERED_SEARCH_PATH) :
      LoadLibrary(filename);
  }
  /* Detect if KB2533623 is installed, as LOAD_LIBARY_SEARCH_SYSTEM32 is only
     supported on Windows Vista, Windows Server 2008, Windows 7 and Windows
     Server 2008 R2 with this patch or natively on Windows 8 and above */
  else if(pLoadLibraryEx && GetProcAddress(hKernel32, "AddDllDirectory")) {
    /* Load the DLL from the Windows system directory */
    hModule = pLoadLibraryEx(filename, NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
  }
  else {
    /* Attempt to get the Windows system path */
    UINT systemdirlen = GetSystemDirectory(NULL, 0);
    if(systemdirlen) {
      /* Allocate space for the full DLL path (Room for the null terminator
         is included in systemdirlen) */
      size_t filenamelen = _tcslen(filename);
      TCHAR *path = malloc(sizeof(TCHAR) * (systemdirlen + 1 + filenamelen));
      if(path && GetSystemDirectory(path, systemdirlen)) {
        /* Calculate the full DLL path */
        _tcscpy(path + _tcslen(path), TEXT("\\"));
        _tcscpy(path + _tcslen(path), filename);

        /* Load the DLL from the Windows system directory */
        /** !checksrc! disable BANNEDFUNC 1 **/
        hModule = pLoadLibraryEx ?
          pLoadLibraryEx(path, NULL, LOAD_WITH_ALTERED_SEARCH_PATH) :
          LoadLibrary(path);

      }
      free(path);
    }
  }

  return hModule;
}