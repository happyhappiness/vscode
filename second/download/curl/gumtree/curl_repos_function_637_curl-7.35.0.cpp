static DWORD WINAPI select_ws_stdin_wait_thread(LPVOID lpParameter)
{
  HANDLE handle;
  DWORD mode;

  handle = (HANDLE) lpParameter;

  if(GetConsoleMode(handle, &mode))
    WaitForSingleObjectEx(handle, INFINITE, FALSE);
  else
    ReadFile(handle, NULL, 0, &mode, NULL);

  return 0;
}