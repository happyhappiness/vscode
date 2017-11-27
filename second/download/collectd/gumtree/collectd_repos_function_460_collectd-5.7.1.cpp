static int numa_init(void) /* {{{ */
{
  /* Determine the number of nodes on this machine. */
  while (42) {
    char path[PATH_MAX];
    struct stat statbuf = {0};
    int status;

    ssnprintf(path, sizeof(path), NUMA_ROOT_DIR "/node%i", max_node + 1);

    status = stat(path, &statbuf);
    if (status == 0) {
      max_node++;
      continue;
    } else if (errno == ENOENT) {
      break;
    } else /* ((status != 0) && (errno != ENOENT)) */
    {
      char errbuf[1024];
      ERROR("numa plugin: stat(%s) failed: %s", path,
            sstrerror(errno, errbuf, sizeof(errbuf)));
      return (-1);
    }
  }

  DEBUG("numa plugin: Found %i nodes.", max_node + 1);
  return (0);
}