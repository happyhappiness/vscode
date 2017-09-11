  }
  inline void Post(void) {
    sem_post(semPtr);
  }
  #else

 private:
  sem_t sem;

 public:
  inline void Init(int init_val) {
    if (sem_init(&sem, 0, init_val) != 0) {
      utils::Error("Semaphore.Init:%s", strerror(errno));
    }
  }
  inline void Destroy(void) {
    if (sem_destroy(&sem) != 0) {
      utils::Error("Semaphore.Destroy:%s", strerror(errno));
    }
  }
  inline void Wait(void) {
    if (sem_wait(&sem) != 0) {
      utils::Error("Semaphore.Wait:%s", strerror(errno));
    }
  }
  inline void Post(void) {
    if (sem_post(&sem) != 0) {
      utils::Error("Semaphore.Post:%s", strerror(errno));
    }
  }
  #endif
};

// mutex that works with pthread
class Mutex {
 public:
  inline void Init(void) {
    pthread_mutex_init(&mutex, NULL);
  }
  inline void Lock(void) {
    pthread_mutex_lock(&mutex);
  }
  inline void Unlock(void) {
    pthread_mutex_unlock(&mutex);
  }
  inline void Destroy(void) {
    pthread_mutex_destroy(&mutex);
  }

 private:
  friend class ConditionVariable;
  pthread_mutex_t mutex;
};

// conditional variable that uses pthread
class ConditionVariable {
 public:
  // initialize conditional variable
  inline void Init(void) {
    pthread_cond_init(&cond, NULL);
  }
  // destroy the thread
  inline void Destroy(void) {
    pthread_cond_destroy(&cond);
  }
  // wait on the conditional variable
  inline void Wait(Mutex *mutex) {
    pthread_cond_wait(&cond, &(mutex->mutex));
  }
  inline void Broadcast(void) {
    pthread_cond_broadcast(&cond);
  }
  inline void Signal(void) {
    pthread_cond_signal(&cond);
  }

 private:
  pthread_cond_t cond;
};

/*!\brief simple thread class */
class Thread {
 private:
  pthread_t thread;
 public :
  inline void Start(void * entry(void*), void *param) { // NOLINT(*)
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&thread, &attr, entry, param);
  }
  inline int Join(void) {
    void *status;
