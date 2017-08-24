{
  char abspath[PATH_MAX * 2 + 1];
  ssize_t abspath_size;

  if (buffer == NULL || size == NULL || *size == 0)
    return -EINVAL;

  abspath_size = readlink("/proc/curproc/file", abspath, sizeof(abspath));
  if (abspath_size < 0)
    return -errno;

  assert(abspath_size > 0);
  *size -= 1;

  if (*size > abspath_size)
    *size = abspath_size;

  memcpy(buffer, abspath, *size);
  buffer[*size] = '\0';

  return 0;
}