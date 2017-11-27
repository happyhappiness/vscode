static size_t strchomp(char *buffer) /* {{{ */
{
  size_t buffer_len;

  buffer_len = strlen(buffer);
  while ((buffer_len > 0) && ((buffer[buffer_len - 1] == '\r') ||
                              (buffer[buffer_len - 1] == '\n'))) {
    buffer_len--;
    buffer[buffer_len] = 0;
  }

  return buffer_len;
}