int strjoin(char *buffer, size_t buffer_size, char **fields, size_t fields_num,
            const char *sep) {
  size_t avail = 0;
  char *ptr = buffer;
  size_t sep_len = 0;

  size_t buffer_req = 0;

  if (((fields_num != 0) && (fields == NULL)) ||
      ((buffer_size != 0) && (buffer == NULL)))
    return -EINVAL;

  if (buffer != NULL)
    buffer[0] = 0;

  if (buffer_size != 0)
    avail = buffer_size - 1;

  if (sep != NULL)
    sep_len = strlen(sep);

  for (size_t i = 0; i < fields_num; i++) {
    size_t field_len = strlen(fields[i]);

    if (i != 0)
      buffer_req += sep_len;
    buffer_req += field_len;

    if ((i != 0) && (sep_len > 0)) {
      if (sep_len >= avail) {
        /* prevent subsequent iterations from writing to the
         * buffer. */
        avail = 0;
        continue;
      }

      memcpy(ptr, sep, sep_len);

      ptr += sep_len;
      avail -= sep_len;
    }

    if (field_len > avail)
      field_len = avail;

    memcpy(ptr, fields[i], field_len);
    ptr += field_len;

    avail -= field_len;
    if (ptr != NULL)
      *ptr = 0;
  }

  return (int)buffer_req;
}