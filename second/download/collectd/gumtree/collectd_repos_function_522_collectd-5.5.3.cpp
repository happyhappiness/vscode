static int ipc_read_shm (void) /* {{{ */
{
  struct shm_info shm_info;
  int status;

  status = shmctl (/* id = */ 0, SHM_INFO, (void *) &shm_info);
  if (status == -1)
  {
    char errbuf[1024];
    ERROR("ipc plugin: shmctl(2) failed: %s. "
        "Maybe the kernel is not configured for shared memory?",
        sstrerror (errno, errbuf, sizeof (errbuf)));
    return (-1);
  }

  ipc_submit_g("shm", "segments", NULL, shm_info.used_ids);
  ipc_submit_g("shm", "bytes", "total", shm_info.shm_tot * pagesize_g);
  ipc_submit_g("shm", "bytes", "rss", shm_info.shm_rss * pagesize_g);
  ipc_submit_g("shm", "bytes", "swapped", shm_info.shm_swp * pagesize_g);
  return (0);
}