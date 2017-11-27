static meta_data_t *cpy_build_meta(PyObject *meta) {
  meta_data_t *m = meta_data_create();
  if (cpy_build_meta_generic(meta, &cpy_meta_data, (void *)m) < 0) {
    meta_data_destroy(m);
    return NULL;
  }
  return m;
}