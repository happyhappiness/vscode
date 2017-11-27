static int staging_entry_update(const char *host, const char *name, /* {{{ */
                                const char *type, const char *type_instance,
                                size_t ds_index, int ds_type, value_t value) {
  const data_set_t *ds;
  staging_entry_t *se;

  ds = plugin_get_ds(type);
  if (ds == NULL) {
    ERROR("gmond plugin: Looking up type %s failed.", type);
    return -1;
  }

  if (ds->ds_num <= ds_index) {
    ERROR("gmond plugin: Invalid index %zu: %s has only %zu data source(s).",
          ds_index, ds->type, ds->ds_num);
    return -1;
  }

  pthread_mutex_lock(&staging_lock);

  se = staging_entry_get(host, name, type, type_instance, ds->ds_num);
  if (se == NULL) {
    pthread_mutex_unlock(&staging_lock);
    ERROR("gmond plugin: staging_entry_get failed.");
    return -1;
  }
  if (se->vl.values_len != ds->ds_num) {
    pthread_mutex_unlock(&staging_lock);
    return -1;
  }

  if (ds_type == DS_TYPE_COUNTER)
    se->vl.values[ds_index].counter += value.counter;
  else if (ds_type == DS_TYPE_GAUGE)
    se->vl.values[ds_index].gauge = value.gauge;
  else if (ds_type == DS_TYPE_DERIVE)
    se->vl.values[ds_index].derive += value.derive;
  else if (ds_type == DS_TYPE_ABSOLUTE)
    se->vl.values[ds_index].absolute = value.absolute;
  else
    assert(23 == 42);

  se->flags |= (0x01 << ds_index);

  /* Check if all data sources have been set. If not, return here. */
  if (se->flags != ((0x01 << se->vl.values_len) - 1)) {
    pthread_mutex_unlock(&staging_lock);
    return 0;
  }

  /* Check if the interval of this metric is known. If not, request meta data
   * and return. */
  if (se->vl.interval == 0) {
    /* No meta data has been received for this metric yet. */
    se->flags = 0;
    pthread_mutex_unlock(&staging_lock);

    request_meta_data(host, name);
    return 0;
  }

  plugin_dispatch_values(&se->vl);

  se->flags = 0;
  pthread_mutex_unlock(&staging_lock);

  return 0;
}