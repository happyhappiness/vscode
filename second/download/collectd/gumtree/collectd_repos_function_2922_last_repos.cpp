const data_set_t *plugin_get_ds(const char *name) {
  data_set_t *ds;

  if (data_sets == NULL) {
    ERROR("plugin_get_ds: No data sets are defined yet.");
    return NULL;
  }

  if (c_avl_get(data_sets, name, (void *)&ds) != 0) {
    DEBUG("No such dataset registered: %s", name);
    return NULL;
  }

  return ds;
}