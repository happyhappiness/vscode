static int ut_report_state (const data_set_t *ds,
    const value_list_t *vl,
    const threshold_t *th,
    const gauge_t *values,
    int ds_index,
    int state)
{ /* {{{ */
  int state_old;
  notification_t n;

  char *buf;
  size_t bufsize;

  int status;

  /* Check if hits matched */
  if ( (th->hits != 0) )
  {
    int hits = uc_get_hits(ds,vl);
    /* The STATE_OKAY always reset hits, or if hits reaise the limit */
    if ( (state == STATE_OKAY) || (hits > th->hits) )
    {
        DEBUG("ut_report_state: reset uc_get_hits = 0");
        uc_set_hits(ds,vl,0); /* reset hit counter and notify */
    } else {
      DEBUG("ut_report_state: th->hits = %d, uc_get_hits = %d",th->hits,uc_get_hits(ds,vl));
      (void) uc_inc_hits(ds,vl,1); /* increase hit counter */
      return (0);
    }
  } /* end check hits */

  state_old = uc_get_state (ds, vl);

  /* If the state didn't change, only report if `persistent' is specified and
   * the state is not `okay'. */
  if (state == state_old)
  {
    if ((th->flags & UT_FLAG_PERSIST) == 0)
      return (0);
    else if (state == STATE_OKAY)
      return (0);
  }

  if (state != state_old)
    uc_set_state (ds, vl, state);

  NOTIFICATION_INIT_VL (&n, vl, ds);

  buf = n.message;
  bufsize = sizeof (n.message);

  if (state == STATE_OKAY)
    n.severity = NOTIF_OKAY;
  else if (state == STATE_WARNING)
    n.severity = NOTIF_WARNING;
  else
    n.severity = NOTIF_FAILURE;

  n.time = vl->time;

  status = ssnprintf (buf, bufsize, "Host %s, plugin %s",
      vl->host, vl->plugin);
  buf += status;
  bufsize -= status;

  if (vl->plugin_instance[0] != '\0')
  {
    status = ssnprintf (buf, bufsize, " (instance %s)",
	vl->plugin_instance);
    buf += status;
    bufsize -= status;
  }

  status = ssnprintf (buf, bufsize, " type %s", vl->type);
  buf += status;
  bufsize -= status;

  if (vl->type_instance[0] != '\0')
  {
    status = ssnprintf (buf, bufsize, " (instance %s)",
	vl->type_instance);
    buf += status;
    bufsize -= status;
  }

  plugin_notification_meta_add_string (&n, "DataSource",
      ds->ds[ds_index].name);
  plugin_notification_meta_add_double (&n, "CurrentValue", values[ds_index]);
  plugin_notification_meta_add_double (&n, "WarningMin", th->warning_min);
  plugin_notification_meta_add_double (&n, "WarningMax", th->warning_max);
  plugin_notification_meta_add_double (&n, "FailureMin", th->failure_min);
  plugin_notification_meta_add_double (&n, "FailureMax", th->failure_max);

  /* Send an okay notification */
  if (state == STATE_OKAY)
  {
    status = ssnprintf (buf, bufsize, ": All data sources are within range again.");
    buf += status;
    bufsize -= status;
  }
  else
  {
    double min;
    double max;

    min = (state == STATE_ERROR) ? th->failure_min : th->warning_min;
    max = (state == STATE_ERROR) ? th->failure_max : th->warning_max;

    if (th->flags & UT_FLAG_INVERT)
    {
      if (!isnan (min) && !isnan (max))
      {
        status = ssnprintf (buf, bufsize, ": Data source \"%s\" is currently "
            "%f. That is within the %s region of %f%s and %f%s.",
            ds->ds[ds_index].name, values[ds_index],
            (state == STATE_ERROR) ? "failure" : "warning",
            min, ((th->flags & UT_FLAG_PERCENTAGE) != 0) ? "%" : "",
            max, ((th->flags & UT_FLAG_PERCENTAGE) != 0) ? "%" : "");
      }
      else
      {
	status = ssnprintf (buf, bufsize, ": Data source \"%s\" is currently "
	    "%f. That is %s the %s threshold of %f%s.",
	    ds->ds[ds_index].name, values[ds_index],
	    isnan (min) ? "below" : "above",
	    (state == STATE_ERROR) ? "failure" : "warning",
	    isnan (min) ? max : min,
	    ((th->flags & UT_FLAG_PERCENTAGE) != 0) ? "%" : "");
      }
    }
    else /* is not inverted */
    {
      status = ssnprintf (buf, bufsize, ": Data source \"%s\" is currently "
	  "%f. That is %s the %s threshold of %f%s.",
	  ds->ds[ds_index].name, values[ds_index],
	  (values[ds_index] < min) ? "below" : "above",
	  (state == STATE_ERROR) ? "failure" : "warning",
	  (values[ds_index] < min) ? min : max,
	  ((th->flags & UT_FLAG_PERCENTAGE) != 0) ? "%" : "");
    }
    buf += status;
    bufsize -= status;
  }

  plugin_dispatch_notification (&n);

  plugin_notification_meta_free (n.meta);
  return (0);
}