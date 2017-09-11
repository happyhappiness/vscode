inline void Wait(void) {
    if (sem_wait(&sem) != 0) {
      utils::Error("Semaphore.Wait:%s", strerror(errno));
    }
  }