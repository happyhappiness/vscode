int format_kairosdb_initialize(char *buffer, /* {{{ */
                               size_t *ret_buffer_fill,
                               size_t *ret_buffer_free) {
  size_t buffer_fill;
  size_t buffer_free;

  if ((buffer == NULL) || (ret_buffer_fill == NULL) ||
      (ret_buffer_free == NULL))
    return (-EINVAL);

  buffer_fill = *ret_buffer_fill;
  buffer_free = *ret_buffer_free;

  buffer_free = buffer_fill + buffer_free;
  buffer_fill = 0;

  if (buffer_free < 3)
    return (-ENOMEM);

  memset(buffer, 0, buffer_free);
  *ret_buffer_fill = buffer_fill;
  *ret_buffer_free = buffer_free;

  return (0);
}