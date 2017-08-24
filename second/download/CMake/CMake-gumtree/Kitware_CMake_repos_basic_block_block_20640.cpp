{
  HANDLE handle;
  SECURITY_ATTRIBUTES sa;

  sa.nLength = sizeof sa;
  sa.lpSecurityDescriptor = NULL;
  sa.bInheritHandle = TRUE;

  handle = CreateFileW(L"NUL",
                       access,
                       FILE_SHARE_READ | FILE_SHARE_WRITE,
                       &sa,
                       OPEN_EXISTING,
                       0,
                       NULL);
  if (handle == INVALID_HANDLE_VALUE) {
    return GetLastError();
  }

  *handle_ptr = handle;
  return 0;
}