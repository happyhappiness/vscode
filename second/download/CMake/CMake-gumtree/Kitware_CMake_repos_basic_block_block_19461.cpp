{
  if (buffer == NULL || size == 0)
    return -EINVAL;
  else if (size <= process_title.len)
    return -ENOBUFS;

  memcpy(buffer, process_title.str, process_title.len + 1);
  buffer[process_title.len] = '\0';

  return 0;
}