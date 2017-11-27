static int ipc_read_sem(void) /* {{{ */
{
  struct seminfo seminfo;
  union semun arg;
  int status;

  arg.array = (void *)&seminfo;

  status = semctl(/* id = */ 0, /* num = */ 0, SEM_INFO, arg);
  if (status == -1) {
    char errbuf[1024];
    ERROR("ipc plugin: semctl(2) failed: %s. "
          "Maybe the kernel is not configured for semaphores?",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  ipc_submit_g("sem", "count", "arrays", seminfo.semusz);
  ipc_submit_g("sem", "count", "total", seminfo.semaem);

  return 0;
}