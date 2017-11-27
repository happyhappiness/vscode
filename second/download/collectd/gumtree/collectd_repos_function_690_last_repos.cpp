static int ps_count_maps(pid_t pid) {
  FILE *fh;
  char buffer[1024];
  char filename[64];
  int count = 0;

  snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
  if ((fh = fopen(filename, "r")) == NULL) {
    DEBUG("ps_count_maps: Failed to open file `%s'", filename);
    return -1;
  }

  while (fgets(buffer, sizeof(buffer), fh) != NULL) {
    if (strchr(buffer, '\n')) {
      count++;
    }
  } /* while (fgets) */

  if (fclose(fh)) {
    char errbuf[1024];
    WARNING("processes: fclose: %s", sstrerror(errno, errbuf, sizeof(errbuf)));
  }
  return count;
}