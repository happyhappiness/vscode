int ut_check_threshold (const data_set_t *ds, const value_list_t *vl)
{
  threshold_t *th;
  gauge_t *values;
  int i;

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

  for (i = 0; i < ds->ds_num; i++)
  {
    int is_inverted = 0;
    int is_warning = 0;
    int is_failure = 0;

    if ((th->flags & UT_FLAG_INVERT) != 0)
      is_inverted = 1;
    if ((!isnan (th->failure_min) && (th->failure_min > values[i]))
	|| (!isnan (th->failure_max) && (th->failure_max < values[i])))
      is_failure = is_inverted - 1;
    if ((!isnan (th->warning_min) && (th->warning_min > values[i]))
	|| (!isnan (th->warning_max) && (th->warning_max < values[i])))
      is_warning = is_inverted - 1;

    if ((is_failure != 0) || (is_warning != 0))
    {
      notification_t n;
      char *buf;
      size_t bufsize;
      int status;

      double min;
      double max;

      min = (is_failure != 0) ? th->failure_min : th->warning_min;
      max = (is_failure != 0) ? th->failure_max : th->warning_max;

      DEBUG ("ut_check_threshold: ds[%s]: %lf <= !%lf <= %lf (invert: %s)",
	  ds->ds[i].name, min, values[i], max,
	  is_inverted ? "true" : "false");

      /* Copy the associative members */
      NOTIFICATION_INIT_VL (&n, vl, ds);

      n.severity = (is_failure != 0) ? NOTIF_FAILURE : NOTIF_WARNING;
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

      if (is_inverted)
      {
	if (!isnan (min) && !isnan (max))
	{
	  status = snprintf (buf, bufsize, ": Data source \"%s\" is currently "
	      "%f. That is within the %s region of %f and %f.",
	      ds->ds[i].name, values[i],
	      (is_failure != 0) ? "failure" : "warning",
	      min, min);
	}
	else
	{
	  status = snprintf (buf, bufsize, ": Data source \"%s\" is currently "
	      "%f. That is %s the %s threshold of %f.",
	      ds->ds[i].name, values[i],
	      isnan (min) ? "below" : "above",
	      (is_failure != 0) ? "failure" : "warning",
	      isnan (min) ? max : min);
	}
      }
      else /* (!is_inverted) */
      {
	status = snprintf (buf, bufsize, ": Data source \"%s\" is currently "
	    "%f. That is %s the %s threshold of %f.",
	    ds->ds[i].name, values[i],
	    (values[i] < min) ? "below" : "above",
	    (is_failure != 0) ? "failure" : "warning",
	    (values[i] < min) ? min : max);
      }
      buf += status;
      bufsize -= status;

      plugin_dispatch_notification (&n);
    }
  } /* for (i = 0; i < ds->ds_num; i++) */

  sfree (values);

  return (0);
}