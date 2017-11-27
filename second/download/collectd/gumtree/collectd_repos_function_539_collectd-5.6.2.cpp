static int ipc_read_shm(void) /* {{{ */
{
  ipcinfo_shm_t *ipcinfo_shm;
  ipcinfo_shm_t *pshm;
  unsigned int shm_segments = 0;
  size64_t shm_bytes = 0;
  int n;

  ipcinfo_shm = (ipcinfo_shm_t *)ipc_get_info(
      0, GET_IPCINFO_SHM_ALL, IPCINFO_SHM_VERSION, sizeof(ipcinfo_shm_t), &n);
  if (ipcinfo_shm == NULL)
    return -1;

  for (int i = 0, pshm = ipcinfo_shm; i < n; i++, pshm++) {
    shm_segments++;
    shm_bytes += pshm->shm_segsz;
  }
  free(ipcinfo_shm);

  ipc_submit_g("shm", "segments", NULL, shm_segments);
  ipc_submit_g("shm", "bytes", "total", shm_bytes);

  return (0);
}