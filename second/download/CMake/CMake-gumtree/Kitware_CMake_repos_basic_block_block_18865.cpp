{
  char abspath[PATH_MAX * 2 + 1];
  int mib[4];
  size_t abspath_size;

  if (buffer == NULL || size == NULL || *size == 0)
    return -EINVAL;

  mib[0] = CTL_KERN;
  mib[1] = KERN_PROC;
  mib[2] = KERN_PROC_PATHNAME;
  mib[3] = -1;

  abspath_size = sizeof abspath;
  if (sysctl(mib, 4, abspath, &abspath_size, NULL, 0))
    return -errno;

  assert(abspath_size > 0);
  abspath_size -= 1;
  *size -= 1;

  if (*size > abspath_size)
    *size = abspath_size;

  memcpy(buffer, abspath, *size);
  buffer[*size] = '\0';

  return 0;
}