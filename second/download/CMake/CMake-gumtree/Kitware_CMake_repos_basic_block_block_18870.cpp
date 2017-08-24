{
  size_t len;

  if (buffer == NULL || size == 0)
    return -EINVAL;

  if (process_title) {
    len = strlen(process_title) + 1;

    if (size < len)
      return -ENOBUFS;

    memcpy(buffer, process_title, len);
  } else {
    len = 0;
  }

  buffer[len] = '\0';

  return 0;
}