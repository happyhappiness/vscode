{
    /* The given handle is not valid for this process.  Some child
       processes may break if they do not have a valid standard handle,
       so open NUL to give to the child.  */
    SECURITY_ATTRIBUTES sa;
    ZeroMemory(&sa, sizeof(sa));
    sa.nLength = (DWORD)sizeof(sa);
    sa.bInheritHandle = 1;
    *out = CreateFileW(
      L"NUL",
      (isStdIn ? GENERIC_READ : (GENERIC_WRITE | FILE_READ_ATTRIBUTES)),
      FILE_SHARE_READ | FILE_SHARE_WRITE, &sa, OPEN_EXISTING, 0, 0);
    return (*out != INVALID_HANDLE_VALUE) ? ERROR_SUCCESS : GetLastError();
  }