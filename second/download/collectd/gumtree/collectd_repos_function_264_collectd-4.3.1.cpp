gauge_t *uc_get_rate (const data_set_t *ds, const value_list_t *vl)
{
  char name[6 * DATA_MAX_NAME_LEN];
  gauge_t *ret = NULL;
  cache_entry_t *ce = NULL;

  if (FORMAT_VL (name, sizeof (name), vl, ds) != 0)
  {
    ERROR ("uc_insert: FORMAT_VL failed.");
    return (NULL);
  }

  pthread_mutex_lock (&cache_lock);

  if (c_avl_get (cache_tree, name, (void *) &ce) == 0)
  {
    assert (ce != NULL);
    assert (ce->values_num == ds->ds_num);

    ret = (gauge_t *) malloc (ce->values_num * sizeof (gauge_t));
    if (ret == NULL)
    {
      ERROR ("uc_get_rate: malloc failed.");
    }
    else
    {
      memcpy (ret, ce->values_gauge, ce->values_num * sizeof (gauge_t));
    }
  }

  pthread_mutex_unlock (&cache_lock);

  return (ret);
}