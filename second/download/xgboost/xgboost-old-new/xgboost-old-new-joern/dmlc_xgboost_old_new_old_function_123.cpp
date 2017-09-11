inline void Init(int init_val) {
    sem_init(&sem, 0, init_val);
  }