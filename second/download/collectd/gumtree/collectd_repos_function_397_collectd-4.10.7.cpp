int uc_update (const data_set_t *ds, const value_list_t *vl)
{
  char name[6 * DATA_MAX_NAME_LEN];
  cache_entry_t *ce = NULL;
  int send_okay_notification = 0;
  time_t update_delay = 0;
  notification_t n;
  int status;
  int i;

  if (FORMAT_VL (name, sizeof (name), vl) != 0)
  {
    ERROR ("uc_update: FORMAT_VL failed.");
    return (-1);
  }

  pthread_mutex_lock (&cache_lock);

  status = c_avl_get (cache_tree, name, (void *) &ce);
  if (status != 0) /* entry does not yet exist */
  {
    status = uc_insert (ds, vl, name);
    pthread_mutex_unlock (&cache_lock);
    return (status);
  }

  assert (ce != NULL);
  assert (ce->values_num == ds->ds_num);

  if (ce->last_time >= vl->time)
  {
    pthread_mutex_unlock (&cache_lock);
    NOTICE ("uc_update: Value too old: name = %s; value time = %u; "
	"last cache update = %u;",
	name, (unsigned int) vl->time, (unsigned int) ce->last_time);
    return (-1);
  }

  /* Send a notification (after the lock has been released) if we switch the
   * state from something else to `okay'. */
  if (ce->state == STATE_MISSING)
  {
    send_okay_notification = 1;
    ce->state = STATE_OKAY;
    update_delay = time (NULL) - ce->last_update;
  }

  for (i = 0; i < ds->ds_num; i++)
  {
    switch (ds->ds[i].type)
    {
      case DS_TYPE_COUNTER:
	{
	  counter_t diff;

	  /* check if the counter has wrapped around */
	  if (vl->values[i].counter < ce->values_raw[i].counter)
	  {
	    if (ce->values_raw[i].counter <= 4294967295U)
	      diff = (4294967295U - ce->values_raw[i].counter)
		+ vl->values[i].counter;
	    else
	      diff = (18446744073709551615ULL - ce->values_raw[i].counter)
		+ vl->values[i].counter;
	  }
	  else /* counter has NOT wrapped around */
	  {
	    diff = vl->values[i].counter - ce->values_raw[i].counter;
	  }

	  ce->values_gauge[i] = ((double) diff)
	    / ((double) (vl->time - ce->last_time));
	  ce->values_raw[i].counter = vl->values[i].counter;
	}
	break;

      case DS_TYPE_GAUGE:
	ce->values_raw[i].gauge = vl->values[i].gauge;
	ce->values_gauge[i] = vl->values[i].gauge;
	break;

      case DS_TYPE_DERIVE:
	{
	  derive_t diff;

	  diff = vl->values[i].derive - ce->values_raw[i].derive;

	  ce->values_gauge[i] = ((double) diff)
	    / ((double) (vl->time - ce->last_time));
	  ce->values_raw[i].derive = vl->values[i].derive;
	}
	break;

      case DS_TYPE_ABSOLUTE:
	ce->values_gauge[i] = ((double) vl->values[i].absolute)
	  / ((double) (vl->time - ce->last_time));
	ce->values_raw[i].absolute = vl->values[i].absolute;
	break;

      default:
	/* This shouldn't happen. */
	pthread_mutex_unlock (&cache_lock);
	ERROR ("uc_update: Don't know how to handle data source type %i.",
	    ds->ds[i].type);
	return (-1);
    } /* switch (ds->ds[i].type) */

    DEBUG ("uc_update: %s: ds[%i] = %lf", name, i, ce->values_gauge[i]);
  } /* for (i) */

  /* Update the history if it exists. */
  if (ce->history != NULL)
  {
    assert (ce->history_index < ce->history_length);
    for (i = 0; i < ce->values_num; i++)
    {
      size_t hist_idx = (ce->values_num * ce->history_index) + i;
      ce->history[hist_idx] = ce->values_gauge[i];
    }

    assert (ce->history_length > 0);
    ce->history_index = (ce->history_index + 1) % ce->history_length;
  }

  /* Prune invalid gauge data */
  uc_check_range (ds, ce);

  ce->last_time = vl->time;
  ce->last_update = time (NULL);
  ce->interval = vl->interval;

  pthread_mutex_unlock (&cache_lock);

  if (send_okay_notification == 0)
    return (0);

  /* Do not send okay notifications for uninteresting values, i. e. values for
   * which no threshold is configured. */
  status = ut_check_interesting (name);
  if (status <= 0)
    return (0);

  /* Initialize the notification */
  memset (&n, '\0', sizeof (n));
  NOTIFICATION_INIT_VL (&n, vl, ds);

  n.severity = NOTIF_OKAY;
  n.time = vl->time;

  ssnprintf (n.message, sizeof (n.message),
      "Received a value for %s. It was missing for %u seconds.",
      name, (unsigned int) update_delay);

  plugin_dispatch_notification (&n);

  return (0);
}