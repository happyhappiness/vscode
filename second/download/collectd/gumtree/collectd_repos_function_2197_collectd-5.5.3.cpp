static int uc_insert (const data_set_t *ds, const value_list_t *vl,
    const char *key)
{
  int i;
  char *key_copy;
  cache_entry_t *ce;

  /* `cache_lock' has been locked by `uc_update' */

  key_copy = strdup (key);
  if (key_copy == NULL)
  {
    ERROR ("uc_insert: strdup failed.");
    return (-1);
  }

  ce = cache_alloc (ds->ds_num);
  if (ce == NULL)
  {
    sfree (key_copy);
    ERROR ("uc_insert: cache_alloc (%i) failed.", ds->ds_num);
    return (-1);
  }

  sstrncpy (ce->name, key, sizeof (ce->name));

  for (i = 0; i < ds->ds_num; i++)
  {
    switch (ds->ds[i].type)
    {
      case DS_TYPE_COUNTER:
	ce->values_gauge[i] = NAN;
	ce->values_raw[i].counter = vl->values[i].counter;
	break;

      case DS_TYPE_GAUGE:
	ce->values_gauge[i] = vl->values[i].gauge;
	ce->values_raw[i].gauge = vl->values[i].gauge;
	break;

      case DS_TYPE_DERIVE:
	ce->values_gauge[i] = NAN;
	ce->values_raw[i].derive = vl->values[i].derive;
	break;

      case DS_TYPE_ABSOLUTE:
	ce->values_gauge[i] = NAN;
	if (vl->interval > 0)
	  ce->values_gauge[i] = ((double) vl->values[i].absolute)
	    / CDTIME_T_TO_DOUBLE (vl->interval);
	ce->values_raw[i].absolute = vl->values[i].absolute;
	break;

      default:
	/* This shouldn't happen. */
	ERROR ("uc_insert: Don't know how to handle data source type %i.",
	    ds->ds[i].type);
	sfree (key_copy);
	cache_free (ce);
	return (-1);
    } /* switch (ds->ds[i].type) */
  } /* for (i) */

  /* Prune invalid gauge data */
  uc_check_range (ds, ce);

  ce->last_time = vl->time;
  ce->last_update = cdtime ();
  ce->interval = vl->interval;
  ce->state = STATE_OKAY;

  if (c_avl_insert (cache_tree, key_copy, ce) != 0)
  {
    sfree (key_copy);
    ERROR ("uc_insert: c_avl_insert failed.");
    return (-1);
  }

  DEBUG ("uc_insert: Added %s to the cache.", key);
  return (0);
}