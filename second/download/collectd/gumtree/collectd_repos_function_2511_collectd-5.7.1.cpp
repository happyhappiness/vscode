size_t strstripnewline(char *buffer) {
  size_t buffer_len = strlen(buffer);

  while (buffer_len > 0) {
    if ((buffer[buffer_len - 1] != '\n') && (buffer[buffer_len - 1] != '\r'))
      break;
    buffer_len--;
    buffer[buffer_len] = 0;
  }

  return (buffer_len);
}