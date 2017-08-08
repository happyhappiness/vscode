{
  ssize_t res;
  char buf[128];

  if (buffer == NULL || size == NULL || *size == 0)
    return -EINVAL;

  snprintf(buf, sizeof(buf), "/proc/%lu/path/a.out", (unsigned long) getpid());

  res = *size - 1;
  if (res > 0)
    res = readlink(buf, buffer, res);

  if (res == -1)
    return -errno;

  buffer[res] = '\0';
  *size = res;
  return 0;
}