inline void Wait(void) {
    utils::Check(WaitForSingleObject(sem, INFINITE) == WAIT_OBJECT_0, "WaitForSingleObject error");
  }