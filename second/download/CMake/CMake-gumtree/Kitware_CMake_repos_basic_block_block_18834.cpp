{
  if (unsetenv(name) != 0)
    return -errno;

  return 0;
}