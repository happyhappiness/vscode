(this->LockFile(F_SETLK, F_WRLCK) == -1) {
      if (errno != EACCES && errno != EAGAIN) {
        return cmFileLockResult::MakeSystem();
      }
    } else {
      return cmFileLockResult::MakeOk();
    }