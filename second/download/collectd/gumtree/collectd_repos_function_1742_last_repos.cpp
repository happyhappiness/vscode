static void ovs_json_reader_reset(ovs_json_reader_t *jreader) {
  if (jreader) {
    jreader->buff_offset = 0;
    jreader->json_offset = 0;
  }
}