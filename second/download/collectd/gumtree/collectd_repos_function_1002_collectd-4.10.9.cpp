static int staging_entry_update (const char *host, const char *name, /* {{{ */
    const char *type, const char *type_instance,
    int ds_index, int ds_type, value_t value)
{
  const data_set_t *ds;
  staging_entry_t *se;

  ds = plugin_get_ds (type);
  if (ds == NULL)
  {
    ERROR ("gmond plugin: Looking up type %s failed.", type);
    return (-1);
  }

  if (ds->ds_num <= ds_index)
  {
    ERROR ("gmond plugin: Invalid index %i: %s has only %i data source(s).",
        ds_index, ds->type, ds->ds_num);
    return (-1);
  }

  pthread_mutex_lock (&staging_lock);

  se = staging_entry_get (host, name, type, type_instance, ds->ds_num);
  if (se == NULL)
  {
    pthread_mutex_unlock (&staging_lock);
    ERROR ("gmond plugin: staging_entry_get failed.");
    return (-1);
  }
  if (se->vl.values_len != ds->ds_num)
  {
    pthread_mutex_unlock (&staging_lock);
    return (-1);
  }

  if (ds_type == DS_TYPE_COUNTER)
    se->vl.values[ds_index].counter += value.counter;
  else if (ds_type == DS_TYPE_GAUGE)
    se->vl.values[ds_index].gauge = value.gauge;
  else if (ds_type == DS_TYPE_DERIVE)
    se->vl.values[ds_index].derive += value.derive;
  else if (ds_type == DS_TYPE_ABSOLUTE)
    se->vl.values[ds_index].absolute = value.absolute;

  se->flags |= (0x01 << ds_index);

  /* Check if all values have been set and submit if so. */
  if (se->flags == ((0x01 << se->vl.values_len) - 1))
  {
    /* `staging_lock' is unlocked in `staging_entry_submit'. */
    staging_entry_submit (host, name, se);
  }
  else
  {
    pthread_mutex_unlock (&staging_lock);
  }

  return (0);
}