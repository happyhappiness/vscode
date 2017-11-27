static int cpu_stage(size_t cpu_num, size_t state, derive_t d,
                     cdtime_t now) /* {{{ */
{
  int status;
  cpu_state_t *s;
  gauge_t rate = NAN;
  value_t val = {.derive = d};

  if (state >= COLLECTD_CPU_STATE_ACTIVE)
    return EINVAL;

  status = cpu_states_alloc(cpu_num);
  if (status != 0)
    return status;

  if (global_cpu_num <= cpu_num)
    global_cpu_num = cpu_num + 1;

  s = get_cpu_state(cpu_num, state);

  status = value_to_rate(&rate, val, DS_TYPE_DERIVE, now, &s->conv);
  if (status != 0)
    return status;

  s->rate = rate;
  s->has_value = 1;
  return 0;
}