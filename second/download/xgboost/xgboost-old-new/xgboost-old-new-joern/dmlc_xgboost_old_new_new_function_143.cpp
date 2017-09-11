inline void Init(int init_val) {
    sem = CreateSemaphore(NULL, init_val, 10, NULL);
    utils::Check(sem != NULL, "create Semaphore error");
  }