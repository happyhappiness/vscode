static int ovs_json_reader_pop(ovs_json_reader_t *jreader,
                               const char **json_ptr, size_t *json_len_ptr) {
  size_t nbraces = 0;
  size_t json_len = 0;
  char *json = NULL;

  /* search open/close brace */
  for (size_t i = jreader->json_offset; i < jreader->buff_offset; i++) {
    if (jreader->buff_ptr[i] == '{') {
      nbraces++;
    } else if (jreader->buff_ptr[i] == '}')
      if (nbraces)
        if (!(--nbraces)) {
          /* JSON data */
          *json_ptr = jreader->buff_ptr + jreader->json_offset;
          *json_len_ptr = json_len + 1;
          jreader->json_offset = i + 1;
          return 0;
        }

    /* increase JSON data length */
    if (nbraces)
      json_len++;
  }

  if (jreader->json_offset) {
    if (jreader->json_offset < jreader->buff_offset) {
      /* shift data to the beginning of the buffer
       * and zero rest of the buffer data */
      json = &jreader->buff_ptr[jreader->json_offset];
      json_len = jreader->buff_offset - jreader->json_offset;
      for (size_t i = 0; i < jreader->buff_size; i++)
        jreader->buff_ptr[i] = ((i < json_len) ? (json[i]) : (0));
      jreader->buff_offset = json_len;
    } else
      /* reset the buffer */
      jreader->buff_offset = 0;

    /* data is at the beginning of the buffer */
    jreader->json_offset = 0;
  }

  return -1;
}