{
    err = errno;
    if (-1 == semctl(*sem, 0, IPC_RMID))
      abort();
    return -err;
  }