static char const *escape_label_value(char *buffer, size_t buffer_size,
                                      char const *value) {
  /* shortcut for values that don't need escaping. */
  if (strpbrk(value, "\n\"\\") == NULL)
    return value;

  size_t value_len = strlen(value);
  size_t buffer_len = 0;

  for (size_t i = 0; i < value_len; i++) {
    switch (value[i]) {
    case '\n':
    case '"':
    case '\\':
      if ((buffer_size - buffer_len) < 3) {
        break;
      }
      buffer[buffer_len] = '\\';
      buffer[buffer_len + 1] = (value[i] == '\n') ? 'n' : value[i];
      buffer_len += 2;
      break;

    default:
      if ((buffer_size - buffer_len) < 2) {
        break;
      }
      buffer[buffer_len] = value[i];
      buffer_len++;
      break;
    }
  }

  assert(buffer_len < buffer_size);
  buffer[buffer_len] = 0;
  return buffer;
}