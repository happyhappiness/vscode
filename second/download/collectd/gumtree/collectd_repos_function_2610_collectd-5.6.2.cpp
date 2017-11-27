int plugin_register_data_set(const data_set_t *ds) {
  data_set_t *ds_copy;

  if ((data_sets != NULL) && (c_avl_get(data_sets, ds->type, NULL) == 0)) {
    NOTICE("Replacing DS `%s' with another version.", ds->type);
    plugin_unregister_data_set(ds->type);
  } else if (data_sets == NULL) {
    data_sets = c_avl_create((int (*)(const void *, const void *))strcmp);
    if (data_sets == NULL)
      return (-1);
  }

  ds_copy = malloc(sizeof(*ds_copy));
  if (ds_copy == NULL)
    return (-1);
  memcpy(ds_copy, ds, sizeof(data_set_t));

  ds_copy->ds = malloc(sizeof(*ds_copy->ds) * ds->ds_num);
  if (ds_copy->ds == NULL) {
    sfree(ds_copy);
    return (-1);
  }

  for (size_t i = 0; i < ds->ds_num; i++)
    memcpy(ds_copy->ds + i, ds->ds + i, sizeof(data_source_t));

  return (c_avl_insert(data_sets, (void *)ds_copy->type, (void *)ds_copy));
}