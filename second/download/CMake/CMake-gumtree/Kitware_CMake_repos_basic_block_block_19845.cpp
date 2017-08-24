(-1 == semop(semid, &buf, 1)) {
    err = errno;
    if (-1 == semctl(*sem, 0, IPC_RMID))
      abort();
    return -err;
  }