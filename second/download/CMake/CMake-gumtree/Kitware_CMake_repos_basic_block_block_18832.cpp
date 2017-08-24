{
  if (name == NULL || value == NULL)
    return -EINVAL;

  if (setenv(name, value, 1) != 0)
    return -errno;

  return 0;
}