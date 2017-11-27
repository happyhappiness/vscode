static int cpusleep_read(void) {
  struct timespec b, m;
  if (clock_gettime(CLOCK_BOOTTIME, &b) < 0) {
    ERROR("cpusleep plugin: clock_boottime failed");
    return -1;
  }

  if (clock_gettime(CLOCK_MONOTONIC, &m) < 0) {
    ERROR("cpusleep plugin: clock_monotonic failed");
    return -1;
  }

  // to avoid false positives in counter overflow due to reboot,
  // derive is used. Sleep is calculated in milliseconds
  derive_t diffsec = b.tv_sec - m.tv_sec;
  derive_t diffnsec = b.tv_nsec - m.tv_nsec;
  derive_t sleep = diffsec * 1000 + diffnsec / 1000000;

  cpusleep_submit(sleep);

  return 0;
}