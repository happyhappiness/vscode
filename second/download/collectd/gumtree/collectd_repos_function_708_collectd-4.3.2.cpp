int ut_check_threshold (const data_set_t *ds, const value_list_t *vl)
{
  notification_t n;
  threshold_t *th;
  gauge_t *values;
  int i;

  int state_orig;
  int state_new = STATE_OKAY;
  int ds_index = 0;

  char *buf;
  size_t bufsize;
  int status;

  if (threshold_tree == NULL)
    return (0);

  /* Is this lock really necessary? So far, thresholds are only inserted at
   * startup. -octo */
  pthread_mutex_lock (&threshold_lock);
  th = threshold_search (ds, vl);
  pthread_mutex_unlock (&threshold_lock);
  if (th == NULL)
    return (0);

  DEBUG ("ut_check_threshold: Found matching threshold");

  values = uc_get_rate (ds, vl);
  if (values == NULL)
    return (0);

  state_orig = uc_get_state (ds, vl);

  for (i = 0; i < ds->ds_num; i++)
  {
    int is_inverted = 0;
    int is_warning = 0;
    int is_failure = 0;

    if ((th->flags & UT_FLAG_INVERT) != 0)
    {
      is_inverted = 1;
      is_warning--;
      is_failure--;
    }
    if ((!isnan (th->failure_min) && (th->failure_min > values[i]))
	|| (!isnan (th->failure_max) && (th->failure_max < values[i])))
      is_failure++;
    if ((!isnan (th->warning_min) && (th->warning_min > values[i]))
	|| (!isnan (th->warning_max) && (th->warning_max < values[i])))
      is_warning++;

    if ((is_failure != 0) && (state_new != STATE_ERROR))
    {
      state_new = STATE_ERROR;
      ds_index = i;
    }
    else if ((is_warning != 0)
	&& (state_new != STATE_ERROR)
	&& (state_new != STATE_WARNING))
    {
      state_new = STATE_WARNING;
      ds_index = i;
    }
  }

  if (state_new != state_orig)
    uc_set_state (ds, vl, state_new);

  /* Return here if we're not going to send a notification */
  if ((state_new == state_orig)
      && ((state_new == STATE_OKAY)
	|| ((th->flags & UT_FLAG_PERSIST) == 0)))
  {
    sfree (values);
    return (0);
  }

  NOTIFICATION_INIT_VL (&n, vl, ds);
  {
    /* Copy the associative members */
    if (state_new == STATE_OKAY)
      n.severity = NOTIF_OKAY;
    else if (state_new == STATE_WARNING)
      n.severity = NOTIF_WARNING;
    else
      n.severity = NOTIF_FAILURE;

    n.time = vl->time;

    buf = n.message;
    bufsize = sizeof (n.message);

    status = snprintf (buf, bufsize, "Host %s, plugin %s",
	vl->host, vl->plugin);
    buf += status;
    bufsize -= status;

    if (vl->plugin_instance[0] != '\0')
    {
      status = snprintf (buf, bufsize, " (instance %s)",
	  vl->plugin_instance);
      buf += status;
      bufsize -= status;
    }

    status = snprintf (buf, bufsize, " type %s", ds->type);
    buf += status;
    bufsize -= status;

    if (vl->type_instance[0] != '\0')
    {
      status = snprintf (buf, bufsize, " (instance %s)",
	  vl->type_instance);
      buf += status;
      bufsize -= status;
    }
  }

  /* Send a okay notification */
  if (state_new == STATE_OKAY)
  {
    status = snprintf (buf, bufsize, ": All data sources are within range again.");
    buf += status;
    bufsize -= status;
  }
  else
  {
    double min;
    double max;

    min = (state_new == STATE_ERROR) ? th->failure_min : th->warning_min;
    max = (state_new == STATE_ERROR) ? th->failure_max : th->warning_max;

    if (th->flags & UT_FLAG_INVERT)
    {
      if (!isnan (min) && !isnan (max))
      {
	status = snprintf (buf, bufsize, ": Data source \"%s\" is currently "
	    "%f. That is within the %s region of %f and %f.",
	    ds->ds[ds_index].name, values[ds_index],
	    (state_new == STATE_ERROR) ? "failure" : "warning",
	    min, min);
      }
      else
      {
	status = snprintf (buf, bufsize, ": Data source \"%s\" is currently "
	    "%f. That is %s the %s threshold of %f.",
	    ds->ds[ds_index].name, values[ds_index],
	    isnan (min) ? "below" : "above",
	    (state_new == STATE_ERROR) ? "failure" : "warning",
	    isnan (min) ? max : min);
      }
    }
    else /* is not inverted */
    {
      status = snprintf (buf, bufsize, ": Data source \"%s\" is currently "
	  "%f. That is %s the %s threshold of %f.",
	  ds->ds[ds_index].name, values[ds_index],
	  (values[ds_index] < min) ? "below" : "above",
	  (state_new == STATE_ERROR) ? "failure" : "warning",
	  (values[ds_index] < min) ? min : max);
    }
    buf += status;
    bufsize -= status;
  }

  plugin_dispatch_notification (&n);

  sfree (values);

  return (0);
}