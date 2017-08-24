(true) {
    if (this->LockFile(F_SETLK, F_WRLCK) == -1) {
      if (errno != EACCES && errno != EAGAIN) {
        return cmFileLockResult::MakeSystem();
      }
    } else {
      return cmFileLockResult::MakeOk();
    }
    if (seconds == 0) {
      return cmFileLockResult::MakeTimeout();
    }
    --seconds;
    cmSystemTools::Delay(1000);
  }