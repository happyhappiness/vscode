int format_json_finalize(char *buffer, /* {{{ */
                         size_t *ret_buffer_fill, size_t *ret_buffer_free) {
  size_t pos;

  if ((buffer == NULL) || (ret_buffer_fill == NULL) ||
      (ret_buffer_free == NULL))
    return (-EINVAL);

  if (*ret_buffer_free < 2)
    return (-ENOMEM);

  /* Replace the leading comma added in `value_list_to_json' with a square
   * bracket. */
  if (buffer[0] != ',')
    return (-EINVAL);
  buffer[0] = '[';

  pos = *ret_buffer_fill;
  buffer[pos] = ']';
  buffer[pos + 1] = 0;

  (*ret_buffer_fill)++;
  (*ret_buffer_free)--;

  return (0);
}