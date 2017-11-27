static void ovs_json_reader_free(ovs_json_reader_t *jreader) {
  if (jreader) {
    free(jreader->buff_ptr);
    free(jreader);
  }
}