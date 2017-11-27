static int dstypes_to_json(char *buffer, size_t buffer_size, /* {{{ */
                           const data_set_t *ds) {
  size_t offset = 0;

  memset(buffer, 0, buffer_size);

#define BUFFER_ADD(...)                                                        \
  do {                                                                         \
    int status;                                                                \
    status = ssnprintf(buffer + offset, buffer_size - offset, __VA_ARGS__);    \
    if (status < 1)                                                            \
      return (-1);                                                             \
    else if (((size_t)status) >= (buffer_size - offset))                       \
      return (-ENOMEM);                                                        \
    else                                                                       \
      offset += ((size_t)status);                                              \
  } while (0)

  BUFFER_ADD("[");
  for (size_t i = 0; i < ds->ds_num; i++) {
    if (i > 0)
      BUFFER_ADD(",");

    BUFFER_ADD("\"%s\"", DS_TYPE_TO_STRING(ds->ds[i].type));
  } /* for ds->ds_num */
  BUFFER_ADD("]");

#undef BUFFER_ADD

  DEBUG("format_json: dstypes_to_json: buffer = %s;", buffer);

  return (0);
}