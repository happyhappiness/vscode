static int dpdk_event_keep_alive_shm_open(void) {
  dpdk_events_ctx_t *ec = DPDK_EVENTS_CTX_GET(g_hc);
  char *shm_name;

  if (strlen(ec->config.keep_alive.shm_name)) {
    shm_name = ec->config.keep_alive.shm_name;
  } else {
    shm_name = RTE_KEEPALIVE_SHM_NAME;
    WARNING(DPDK_EVENTS_PLUGIN ": Keep alive shared memory identifier is not "
                               "specified, using default one: %s",
            shm_name);
  }

  char errbuf[ERR_BUF_SIZE];
  int fd = shm_open(shm_name, O_RDONLY, 0);
  if (fd < 0) {
    ERROR(DPDK_EVENTS_PLUGIN ": Failed to open %s as SHM:%s. Is DPDK KA "
                             "primary application running?",
          shm_name, sstrerror(errno, errbuf, sizeof(errbuf)));
    return errno;
  }

  if (ec->config.keep_alive.fd != -1) {
    struct stat stat_old, stat_new;

    if (fstat(ec->config.keep_alive.fd, &stat_old) || fstat(fd, &stat_new)) {
      ERROR(DPDK_EVENTS_PLUGIN ": failed to get information about a file");
      close(fd);
      return -1;
    }

    /* Check if inode number has changed. If yes, then create a new mapping */
    if (stat_old.st_ino == stat_new.st_ino) {
      close(fd);
      return 0;
    }

    if (munmap(ec->config.keep_alive.shm, sizeof(dpdk_keepalive_shm_t)) != 0) {
      ERROR(DPDK_EVENTS_PLUGIN ": munmap KA monitor failed");
      close(fd);
      return -1;
    }

    close(ec->config.keep_alive.fd);
    ec->config.keep_alive.fd = -1;
  }

  ec->config.keep_alive.shm = (dpdk_keepalive_shm_t *)mmap(
      0, sizeof(*(ec->config.keep_alive.shm)), PROT_READ, MAP_SHARED, fd, 0);
  if (ec->config.keep_alive.shm == MAP_FAILED) {
    ERROR(DPDK_EVENTS_PLUGIN ": Failed to mmap KA SHM:%s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    close(fd);
    return errno;
  }
  ec->config.keep_alive.fd = fd;

  return 0;
}