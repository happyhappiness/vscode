int uc_update (const data_set_t *ds, const value_list_t *vl)
{
  char name[6 * DATA_MAX_NAME_LEN];
  cache_entry_t *ce = NULL;
  int send_okay_notification = 0;

  if (FORMAT_VL (name, sizeof (name), vl, ds) != 0)
  {
    ERROR ("uc_insert: FORMAT_VL failed.");
    return (-1);
  }

  pthread_mutex_lock (&cache_lock);

  if (c_avl_get (cache_tree, name, (void *) &ce) == 0)
  {
    int i;

    assert (ce != NULL);
    assert (ce->values_num == ds->ds_num);

    if (ce->last_time >= vl->time)
    {
      pthread_mutex_unlock (&cache_lock);
      NOTICE ("uc_insert: Value too old: name = %s; value time = %u; "
	  "last cache update = %u;",
	  name, (unsigned int) vl->time, (unsigned int) ce->last_time);
      return (-1);
    }

    if ((ce->last_time + ce->interval) < vl->time)
    {
      send_okay_notification = vl->time - ce->last_time;
      ce->state = STATE_OKAY;
    }

    for (i = 0; i < ds->ds_num; i++)
    {
      if (ds->ds[i].type == DS_TYPE_COUNTER)
      {
	counter_t diff;

	/* check if the counter has wrapped around */
	if (vl->values[i].counter < ce->values_counter[i])
	{
	  if (ce->values_counter[i] <= 4294967295U)
	    diff = (4294967295U - ce->values_counter[i])
	      + vl->values[i].counter;
	  else
	    diff = (18446744073709551615ULL - ce->values_counter[i])
	      + vl->values[i].counter;
	}
	else /* counter has NOT wrapped around */
	{
	  diff = vl->values[i].counter - ce->values_counter[i];
	}

	ce->values_gauge[i] = ((double) diff)
	  / ((double) (vl->time - ce->last_time));
	ce->values_counter[i] = vl->values[i].counter;
      }
      else /* if (ds->ds[i].type == DS_TYPE_GAUGE) */
      {
	ce->values_gauge[i] = vl->values[i].gauge;
      }
      DEBUG ("uc_insert: %s: ds[%i] = %lf", name, i, ce->values_gauge[i]);
    } /* for (i) */

    ce->last_time = vl->time;
    ce->last_update = time (NULL);
    ce->interval = vl->interval;
  }
  else /* key is not found */
  {
    int i;
    size_t ce_size = sizeof (cache_entry_t)
      + ds->ds_num * (sizeof (counter_t) + sizeof (gauge_t));
    char *key;
    
    key = strdup (name);
    if (key == NULL)
    {
      pthread_mutex_unlock (&cache_lock);
      ERROR ("uc_insert: strdup failed.");
      return (-1);
    }

    ce = (cache_entry_t *) malloc (ce_size);
    if (ce == NULL)
    {
      pthread_mutex_unlock (&cache_lock);
      ERROR ("uc_insert: malloc (%u) failed.", (unsigned int) ce_size);
      return (-1);
    }

    memset (ce, '\0', ce_size);

    strncpy (ce->name, name, sizeof (ce->name));
    ce->name[sizeof (ce->name) - 1] = '\0';

    ce->values_num = ds->ds_num;
    ce->values_gauge = (gauge_t *) (ce + 1);
    ce->values_counter = (counter_t *) (ce->values_gauge + ce->values_num);

    for (i = 0; i < ds->ds_num; i++)
    {
      if (ds->ds[i].type == DS_TYPE_COUNTER)
      {
	ce->values_gauge[i] = NAN;
	ce->values_counter[i] = vl->values[i].counter;
      }
      else /* if (ds->ds[i].type == DS_TYPE_GAUGE) */
      {
	ce->values_gauge[i] = vl->values[i].gauge;
      }
    } /* for (i) */

    ce->last_time = vl->time;
    ce->last_update = time (NULL);
    ce->interval = vl->interval;
    ce->state = STATE_OKAY;

    if (c_avl_insert (cache_tree, key, ce) != 0)
    {
      pthread_mutex_unlock (&cache_lock);
      ERROR ("uc_insert: c_avl_insert failed.");
      return (-1);
    }

    DEBUG ("uc_insert: Added %s to the cache.", name);
  } /* if (key is not found) */

  pthread_mutex_unlock (&cache_lock);

  /* Do not send okay notifications for uninteresting values, i. e. values for
   * which no threshold is configured. */
  if (send_okay_notification > 0)
  {
    int status;

    status = ut_check_interesting (name);
    if (status <= 0)
      send_okay_notification = 0;
  }

  if (send_okay_notification > 0)
  {
    notification_t n;
    memset (&n, '\0', sizeof (n));

    /* Copy the associative members */
    NOTIFICATION_INIT_VL (&n, vl, ds);

    n.severity = NOTIF_OKAY;
    n.time = vl->time;

    snprintf (n.message, sizeof (n.message),
	"Received a value for %s. It was missing for %i seconds.",
	name, send_okay_notification);
    n.message[sizeof (n.message) - 1] = '\0';

    plugin_dispatch_notification (&n);
  }

  return (0);
}