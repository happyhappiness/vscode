{
  if (this->Filename.empty()) {
    return cmFileLockResult::MakeOk();
  }
  const unsigned long len = static_cast<unsigned long>(-1);
  static OVERLAPPED overlapped;
  const DWORD reserved = 0;
  const BOOL unlockResult =
    UnlockFileEx(File, reserved, len, len, &overlapped);

  this->Filename = "";

  CloseHandle(this->File);
  this->File = INVALID_HANDLE_VALUE;

  if (unlockResult) {
    return cmFileLockResult::MakeOk();
  } else {
    return cmFileLockResult::MakeSystem();
  }
}