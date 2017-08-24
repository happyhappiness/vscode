(errno != EACCES && errno != EAGAIN) {
        return cmFileLockResult::MakeSystem();
      }