inline void Init(int init_val) {
    if (sem_init(&sem, 0, init_val) != 0) {
      utils::Error("Semaphore.Init:%s", strerror(errno));
    }
  }