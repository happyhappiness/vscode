inline void Destroy(void) {
    if (sem_destroy(&sem) != 0) {
      utils::Error("Semaphore.Destroy:%s", strerror(errno));
    }
  }