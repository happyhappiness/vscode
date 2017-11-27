int uc_inc_hits (const data_set_t *ds, const value_list_t *vl, int step)
{
  char name[6 * DATA_MAX_NAME_LEN];
  cache_entry_t *ce = NULL;
  int ret = -1;

  if (FORMAT_VL (name, sizeof (name), vl) != 0)
  {
    ERROR ("uc_inc_hits: FORMAT_VL failed.");
    return (STATE_ERROR);
  }

  pthread_mutex_lock (&cache_lock);

  if (c_avl_get (cache_tree, name, (void *) &ce) == 0)
  {
    assert (ce != NULL);
    ret = ce->hits;
    ce->hits = ret + step;
  }

  pthread_mutex_unlock (&cache_lock);

  return (ret);
}