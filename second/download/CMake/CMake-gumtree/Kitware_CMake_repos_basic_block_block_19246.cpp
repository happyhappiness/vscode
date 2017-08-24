{
  if (buffer == NULL || size == 0)
    return -EINVAL;

  buffer[0] = '\0';
  return 0;
}