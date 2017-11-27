int escape_slashes(char *buffer, size_t buffer_size) {
  size_t buffer_len;

  buffer_len = strlen(buffer);

  if (buffer_len <= 1) {
    if (strcmp("/", buffer) == 0) {
      if (buffer_size < 5)
        return (-1);
      sstrncpy(buffer, "root", buffer_size);
    }
    return (0);
  }

  /* Move one to the left */
  if (buffer[0] == '/') {
    memmove(buffer, buffer + 1, buffer_len);
    buffer_len--;
  }

  for (size_t i = 0; i < buffer_len; i++) {
    if (buffer[i] == '/')
      buffer[i] = '_';
  }

  return (0);
}