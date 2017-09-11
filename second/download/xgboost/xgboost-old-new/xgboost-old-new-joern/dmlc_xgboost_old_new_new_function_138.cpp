inline void Post(void) {
    if (sem_post(&sem) != 0) {
      utils::Error("Semaphore.Post:%s", strerror(errno));
    }
  }