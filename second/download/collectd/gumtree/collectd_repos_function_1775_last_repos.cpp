static void dpdk_shm_cleanup(const char *name, size_t size, void *map) {
  DPDK_HELPER_TRACE(name);
  char errbuf[ERR_BUF_SIZE];

  /*
   * Call shm_unlink first, as 'name' might be no longer accessible after munmap
   */
  if (shm_unlink(name))
    ERROR("shm_unlink failure %s", sstrerror(errno, errbuf, sizeof(errbuf)));

  if (map != NULL) {
    if (munmap(map, size))
      ERROR("munmap failure %s", sstrerror(errno, errbuf, sizeof(errbuf)));
  }
}