static int dpdk_shm_init(size_t size) {
  /*
   * Check if SHM is already configured: when config items are provided, the
   * config function initializes SHM. If there is no config, then init() will
   * just return.
   */
  if (g_configuration)
    return 0;

  char errbuf[ERR_BUF_SIZE];

  /* Create and open a new object, or open an existing object. */
  int fd = shm_open(DPDK_SHM_NAME, O_CREAT | O_TRUNC | O_RDWR, 0666);
  if (fd < 0) {
    WARNING("dpdkstat:Failed to open %s as SHM:%s", DPDK_SHM_NAME,
            sstrerror(errno, errbuf, sizeof(errbuf)));
    goto fail;
  }
  /* Set the size of the shared memory object. */
  int ret = ftruncate(fd, size);
  if (ret != 0) {
    WARNING("dpdkstat:Failed to resize SHM:%s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    goto fail_close;
  }
  /* Map the shared memory object into this process' virtual address space. */
  g_configuration = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (g_configuration == MAP_FAILED) {
    WARNING("dpdkstat:Failed to mmap SHM:%s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    goto fail_close;
  }
  /*
   * Close the file descriptor, the shared memory object still exists
   * and can only be removed by calling shm_unlink().
   */
  close(fd);

  /* Initialize g_configuration. */
  memset(g_configuration, 0, size);

  /* Initialize the semaphores for SHM use */
  int err = sem_init(&g_configuration->sema_helper_get_stats, 1, 0);
  if (err) {
    ERROR("dpdkstat semaphore init failed: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    goto close;
  }
  err = sem_init(&g_configuration->sema_stats_in_shm, 1, 0);
  if (err) {
    ERROR("dpdkstat semaphore init failed: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    goto close;
  }

  g_configuration->xstats = NULL;

  return 0;

fail_close:
  close(fd);
fail:
  /* Reset to zero, as it was set to MAP_FAILED aka: (void *)-1. Avoid
   * an issue if collectd attempts to run this plugin failure.
   */
  g_configuration = 0;
  return -1;
}