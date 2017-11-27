static ovs_json_reader_t *ovs_json_reader_alloc() {
  ovs_json_reader_t *jreader = NULL;

  if ((jreader = calloc(sizeof(ovs_json_reader_t), 1)) == NULL)
    return NULL;

  return jreader;
}