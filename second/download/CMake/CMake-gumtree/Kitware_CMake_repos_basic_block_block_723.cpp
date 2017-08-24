(true) {
    const BOOL result = this->LockFile(flags);
    if (result) {
      return cmFileLockResult::MakeOk();
    }
    const DWORD error = GetLastError();
    if (error != ERROR_LOCK_VIOLATION) {
      return cmFileLockResult::MakeSystem();
    }
    if (seconds == 0) {
      return cmFileLockResult::MakeTimeout();
    }
    --seconds;
    cmSystemTools::Delay(1000);
  }