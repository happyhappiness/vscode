static int ipc_read_sem(void) /* {{{ */
{
  ipcinfo_sem_t *ipcinfo_sem;
  unsigned short sem_nsems = 0;
  unsigned short sems = 0;
  int n;

  ipcinfo_sem = (ipcinfo_sem_t *)ipc_get_info(
      0, GET_IPCINFO_SEM_ALL, IPCINFO_SEM_VERSION, sizeof(ipcinfo_sem_t), &n);
  if (ipcinfo_sem == NULL)
    return -1;

  for (int i = 0; i < n; i++) {
    sem_nsems += ipcinfo_sem[i].sem_nsems;
    sems++;
  }
  free(ipcinfo_sem);

  ipc_submit_g("sem", "count", "arrays", sem_nsems);
  ipc_submit_g("sem", "count", "total", sems);

  return (0);
}