int value_to_rate(gauge_t *ret_rate, /* {{{ */
                  value_t value, int ds_type, cdtime_t t,
                  value_to_rate_state_t *state) {
  gauge_t interval;

  /* Another invalid state: The time is not increasing. */
  if (t <= state->last_time) {
    memset(state, 0, sizeof(*state));
    return (EINVAL);
  }

  interval = CDTIME_T_TO_DOUBLE(t - state->last_time);

  /* Previous value is invalid. */
  if (state->last_time == 0) {
    state->last_value = value;
    state->last_time = t;
    return (EAGAIN);
  }

  switch (ds_type) {
  case DS_TYPE_DERIVE: {
    derive_t diff = value.derive - state->last_value.derive;
    *ret_rate = ((gauge_t)diff) / ((gauge_t)interval);
    break;
  }
  case DS_TYPE_GAUGE: {
    *ret_rate = value.gauge;
    break;
  }
  case DS_TYPE_COUNTER: {
    counter_t diff = counter_diff(state->last_value.counter, value.counter);
    *ret_rate = ((gauge_t)diff) / ((gauge_t)interval);
    break;
  }
  case DS_TYPE_ABSOLUTE: {
    absolute_t diff = value.absolute;
    *ret_rate = ((gauge_t)diff) / ((gauge_t)interval);
    break;
  }
  default:
    return EINVAL;
  }

  state->last_value = value;
  state->last_time = t;
  return (0);
}