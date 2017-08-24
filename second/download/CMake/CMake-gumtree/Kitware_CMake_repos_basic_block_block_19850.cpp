{
  struct sembuf buf;
  int op_status;

  buf.sem_num = 0;
  buf.sem_op = -1;
  buf.sem_flg = IPC_NOWAIT;

  do
    op_status = semop(*sem, &buf, 1);
  while (op_status == -1 && errno == EINTR);

  if (op_status) {
    if (errno == EAGAIN)
      return -EAGAIN;
    abort();
  }

  return 0;
}