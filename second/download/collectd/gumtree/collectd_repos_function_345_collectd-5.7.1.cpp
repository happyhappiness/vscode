static int total_rate(gauge_t *sum_by_state, size_t state, derive_t d,
                      value_to_rate_state_t *conv, cdtime_t now) {
  gauge_t rate = NAN;
  int status =
      value_to_rate(&rate, (value_t){.derive = d}, DS_TYPE_DERIVE, now, conv);
  if (status != 0)
    return (status);

  sum_by_state[state] = rate;

  if (state != COLLECTD_CPU_STATE_IDLE)
    RATE_ADD(sum_by_state[COLLECTD_CPU_STATE_ACTIVE], sum_by_state[state]);
  return (0);
}