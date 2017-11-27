static int agg_instance_read_func (agg_instance_t *inst, /* {{{ */
  char const *func, gauge_t rate, rate_to_value_state_t *state,
  value_list_t *vl, char const *pi_prefix, cdtime_t t)
{
  value_t v;
  int status;

  if (pi_prefix[0] != 0)
    subst_string (vl->plugin_instance, sizeof (vl->plugin_instance),
        pi_prefix, AGG_FUNC_PLACEHOLDER, func);
  else
    sstrncpy (vl->plugin_instance, func, sizeof (vl->plugin_instance));

  status = rate_to_value (&v, rate, state, inst->ds_type, t);
  if (status != 0)
  {
    /* If this is the first iteration and rate_to_value() was asked to return a
     * COUNTER or a DERIVE, it will return EAGAIN. Catch this and handle
     * gracefully. */
    if (status == EAGAIN)
      return (0);

    WARNING ("aggregation plugin: rate_to_value failed with status %i.",
        status);
    return (-1);
  }

  vl->values = &v;
  vl->values_len = 1;

  plugin_dispatch_values (vl);

  vl->values = NULL;
  vl->values_len = 0;

  return (0);
}