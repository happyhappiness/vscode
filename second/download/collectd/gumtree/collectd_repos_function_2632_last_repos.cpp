int uc_update(const data_set_t *ds, const value_list_t *vl) {
  char name[6 * DATA_MAX_NAME_LEN];
  cache_entry_t *ce = NULL;
  int status;

  if (FORMAT_VL(name, sizeof(name), vl) != 0) {
    ERROR("uc_update: FORMAT_VL failed.");
    return -1;
  }

  pthread_mutex_lock(&cache_lock);

  status = c_avl_get(cache_tree, name, (void *)&ce);
  if (status != 0) /* entry does not yet exist */
  {
    status = uc_insert(ds, vl, name);
    pthread_mutex_unlock(&cache_lock);
    return status;
  }

  assert(ce != NULL);
  assert(ce->values_num == ds->ds_num);

  if (ce->last_time >= vl->time) {
    pthread_mutex_unlock(&cache_lock);
    NOTICE("uc_update: Value too old: name = %s; value time = %.3f; "
           "last cache update = %.3f;",
           name, CDTIME_T_TO_DOUBLE(vl->time),
           CDTIME_T_TO_DOUBLE(ce->last_time));
    return -1;
  }

  for (size_t i = 0; i < ds->ds_num; i++) {
    switch (ds->ds[i].type) {
    case DS_TYPE_COUNTER: {
      counter_t diff =
          counter_diff(ce->values_raw[i].counter, vl->values[i].counter);
      ce->values_gauge[i] =
          ((double)diff) / (CDTIME_T_TO_DOUBLE(vl->time - ce->last_time));
      ce->values_raw[i].counter = vl->values[i].counter;
    } break;

    case DS_TYPE_GAUGE:
      ce->values_raw[i].gauge = vl->values[i].gauge;
      ce->values_gauge[i] = vl->values[i].gauge;
      break;

    case DS_TYPE_DERIVE: {
      derive_t diff = vl->values[i].derive - ce->values_raw[i].derive;

      ce->values_gauge[i] =
          ((double)diff) / (CDTIME_T_TO_DOUBLE(vl->time - ce->last_time));
      ce->values_raw[i].derive = vl->values[i].derive;
    } break;

    case DS_TYPE_ABSOLUTE:
      ce->values_gauge[i] = ((double)vl->values[i].absolute) /
                            (CDTIME_T_TO_DOUBLE(vl->time - ce->last_time));
      ce->values_raw[i].absolute = vl->values[i].absolute;
      break;

    default:
      /* This shouldn't happen. */
      pthread_mutex_unlock(&cache_lock);
      ERROR("uc_update: Don't know how to handle data source type %i.",
            ds->ds[i].type);
      return -1;
    } /* switch (ds->ds[i].type) */

    DEBUG("uc_update: %s: ds[%zu] = %lf", name, i, ce->values_gauge[i]);
  } /* for (i) */

  /* Update the history if it exists. */
  if (ce->history != NULL) {
    assert(ce->history_index < ce->history_length);
    for (size_t i = 0; i < ce->values_num; i++) {
      size_t hist_idx = (ce->values_num * ce->history_index) + i;
      ce->history[hist_idx] = ce->values_gauge[i];
    }

    assert(ce->history_length > 0);
    ce->history_index = (ce->history_index + 1) % ce->history_length;
  }

  /* Prune invalid gauge data */
  uc_check_range(ds, ce);

  ce->last_time = vl->time;
  ce->last_update = cdtime();
  ce->interval = vl->interval;

  pthread_mutex_unlock(&cache_lock);

  return 0;
}