const data_set_t *plugin_get_ds(const char *name) {
  if (strcmp(name, "MAGIC"))
    return NULL;

  return &magic;
}