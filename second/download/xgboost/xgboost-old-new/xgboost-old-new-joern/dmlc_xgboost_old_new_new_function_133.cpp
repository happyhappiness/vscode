inline void Post(void) {
    utils::Check(ReleaseSemaphore(sem, 1, NULL) != 0, "ReleaseSemaphore error");
  }