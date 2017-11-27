static int staging_entry_submit (const char *host, const char *name, /* {{{ */
    staging_entry_t *se)
{
  value_list_t vl;
  value_t values[se->vl.values_len];

  if (se->vl.interval == 0)
  {
    /* No meta data has been received for this metric yet. */
    se->flags = 0;
    pthread_mutex_unlock (&staging_lock);
    request_meta_data (host, name);
    return (0);
  }

  se->flags = 0;

  memcpy (values, se->vl.values, sizeof (values));
  memcpy (&vl, &se->vl, sizeof (vl));

  /* Unlock before calling `plugin_dispatch_values'.. */
  pthread_mutex_unlock (&staging_lock);

  vl.values = values;

  plugin_dispatch_values (&vl);

  return (0);
}