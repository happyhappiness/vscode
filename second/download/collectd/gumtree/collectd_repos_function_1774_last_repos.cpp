static int dpdk_shm_init(const char *name, size_t size, void **map) {
  DPDK_HELPER_TRACE(name);

  char errbuf[ERR_BUF_SIZE];

  int fd = shm_open(name, O_CREAT | O_TRUNC | O_RDWR, 0666);
  if (fd < 0) {
    WARNING("dpdk_shm_init: Failed to open %s as SHM:%s", name,
            sstrerror(errno, errbuf, sizeof(errbuf)));
    *map = NULL;
    return -1;
  }

  int ret = ftruncate(fd, size);
  if (ret != 0) {
    WARNING("dpdk_shm_init: Failed to resize SHM:%s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    close(fd);
    *map = NULL;
    dpdk_shm_cleanup(name, size, NULL);
    return -1;
  }

  *map = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (*map == MAP_FAILED) {
    WARNING("dpdk_shm_init:Failed to mmap SHM:%s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    close(fd);
    *map = NULL;
    dpdk_shm_cleanup(name, size, NULL);
    return -1;
  }
  /* File descriptor no longer needed for shared memory operations */
  close(fd);
  memset(*map, 0, size);

  return 0;
}