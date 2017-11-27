static int json_escape_string(char *buffer, size_t buffer_size, /* {{{ */
                              const char *string) {
  size_t dst_pos;

  if ((buffer == NULL) || (string == NULL))
    return -EINVAL;

  if (buffer_size < 3)
    return -ENOMEM;

  dst_pos = 0;

#define BUFFER_ADD(c)                                                          \
  do {                                                                         \
    if (dst_pos >= (buffer_size - 1)) {                                        \
      buffer[buffer_size - 1] = 0;                                             \
      return -ENOMEM;                                                          \
    }                                                                          \
    buffer[dst_pos] = (c);                                                     \
    dst_pos++;                                                                 \
  } while (0)

  /* Escape special characters */
  BUFFER_ADD('"');
  for (size_t src_pos = 0; string[src_pos] != 0; src_pos++) {
    if ((string[src_pos] == '"') || (string[src_pos] == '\\')) {
      BUFFER_ADD('\\');
      BUFFER_ADD(string[src_pos]);
    } else if (string[src_pos] <= 0x001F)
      BUFFER_ADD('?');
    else
      BUFFER_ADD(string[src_pos]);
  } /* for */
  BUFFER_ADD('"');
  buffer[dst_pos] = 0;

#undef BUFFER_ADD

  return 0;
}