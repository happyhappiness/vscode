inline void Init(int init_val) {
    sema_name[0] = '/';
    sema_name[1] = 's';
    sema_name[2] = 'e';
    sema_name[3] = '/';
    GenRandomString(&sema_name[4], 16);
    if ((semPtr = sem_open(sema_name, O_CREAT, 0644, init_val)) == SEM_FAILED) {
      perror("sem_open");
      exit(1);
    }
    utils::Check(semPtr != NULL, "create Semaphore error");
  }