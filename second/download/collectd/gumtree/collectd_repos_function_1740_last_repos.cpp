static int ovs_json_reader_push_data(ovs_json_reader_t *jreader,
                                     const char *data, size_t data_len) {
  char *new_buff = NULL;
  size_t available = jreader->buff_size - jreader->buff_offset;

  /* check/update required memory space */
  if (available < data_len) {
    OVS_DEBUG("Reallocate buffer [size=%d, available=%d required=%d]",
              (int)jreader->buff_size, (int)available, (int)data_len);

    /* allocate new chunk of memory */
    new_buff = realloc(jreader->buff_ptr, (jreader->buff_size + data_len));
    if (new_buff == NULL)
      return -1;

    /* point to new allocated memory */
    jreader->buff_ptr = new_buff;
    jreader->buff_size += data_len;
  }

  /* store input data */
  memcpy(jreader->buff_ptr + jreader->buff_offset, data, data_len);
  jreader->buff_offset += data_len;
  return 0;
}