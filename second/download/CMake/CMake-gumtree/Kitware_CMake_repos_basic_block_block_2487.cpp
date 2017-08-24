{
  BOOL bInheritHandles = FALSE;
  DWORD dwCreationFlags = 0;
  memset(&processInfo, 0, sizeof(processInfo));
  memset(&startupInfo, 0, sizeof(startupInfo));
  startupInfo.cb = sizeof(startupInfo);
  startupInfo.dwFlags = STARTF_USESHOWWINDOW;
  startupInfo.wShowWindow = SW_HIDE;
  if (hIn || hOut || hErr) {
    startupInfo.dwFlags |= STARTF_USESTDHANDLES;
    startupInfo.hStdInput = hIn;
    startupInfo.hStdOutput = hOut;
    startupInfo.hStdError = hErr;
    bInheritHandles = TRUE;
  }

  WCHAR cmd[MAX_PATH];
  if (GetModuleFileNameW(NULL, cmd, MAX_PATH) == 0) {
    std::cerr << "GetModuleFileName failed!" << std::endl;
    return false;
  }
  WCHAR* p = cmd + wcslen(cmd);
  while (p > cmd && *p != L'\\')
    p--;
  *(p + 1) = 0;
  wcscat(cmd, cmdConsoleBufChild);
  wcscat(cmd, L".exe");

  bool success =
    CreateProcessW(NULL,            // No module name (use command line)
                   cmd,             // Command line
                   NULL,            // Process handle not inheritable
                   NULL,            // Thread handle not inheritable
                   bInheritHandles, // Set handle inheritance
                   dwCreationFlags,
                   NULL,         // Use parent's environment block
                   NULL,         // Use parent's starting directory
                   &startupInfo, // Pointer to STARTUPINFO structure
                   &processInfo) !=
    0; // Pointer to PROCESS_INFORMATION structure
  if (!success) {
    DWORD lastError = GetLastError();
    std::cerr << "CreateProcess(" << kwsys::Encoding::ToNarrow(cmd) << ")"
              << std::endl;
    displayError(lastError);
  }
  return success;
}