static void dpdk_helper_check_pipe(dpdk_helper_ctx_t *phc) {
  char buf[DPDK_MAX_BUFFER_SIZE];
  char out[DPDK_MAX_BUFFER_SIZE];

  /* non blocking check on helper logging pipe */
  struct pollfd fds = {
      .fd = phc->pipes[0], .events = POLLIN,
  };
  int data_avail = poll(&fds, 1, 0);
  DEBUG("%s:dpdk_helper_check_pipe: poll data_avail=%d", phc->shm_name,
        data_avail);
  if (data_avail < 0) {
    if (errno != EINTR || errno != EAGAIN) {
      char errbuf[ERR_BUF_SIZE];
      ERROR("%s: poll(2) failed: %s", phc->shm_name,
            sstrerror(errno, errbuf, sizeof(errbuf)));
    }
  }
  while (data_avail) {
    int nbytes = read(phc->pipes[0], buf, (sizeof(buf) - 1));
    DEBUG("%s:dpdk_helper_check_pipe: read nbytes=%d", phc->shm_name, nbytes);
    if (nbytes <= 0)
      break;
    buf[nbytes] = '\0';
    sstrncpy(out, buf, sizeof(out));
    DEBUG("%s: helper process:\n%s", phc->shm_name, out);
  }
}