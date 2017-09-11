inline void Post(void) {
    utils::Assert(ReleaseSemaphore(sem, 1, NULL)  != 0, "ReleaseSemaphore error");
  }