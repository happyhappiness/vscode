BOOL APIENTRY
DllMain (
	 HINSTANCE hInst /* Library instance handle. */ ,
	 DWORD reason /* Reason this function is being called. */ ,
	 LPVOID reserved /* Not used. */ )
{

  switch (reason)
    {
    case DLL_PROCESS_ATTACH:
      break;

    case DLL_PROCESS_DETACH:
      break;

    case DLL_THREAD_ATTACH:
      break;

    case DLL_THREAD_DETACH:
      break;
    }
  return TRUE;
}