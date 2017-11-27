static int dpdk_shutdown(void) {
  int ret = 0;
  char errbuf[ERR_BUF_SIZE];
  close(g_configuration->helper_pipes[1]);
  int err = kill(g_configuration->helper_pid, SIGKILL);
  if (err) {
    ERROR("dpdkstat: error sending sigkill to helper %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    ret = -1;
  }
  err = dpdk_shm_cleanup();
  if (err) {
    ERROR("dpdkstat: error cleaning up SHM: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    ret = -1;
  }

  return ret;
}