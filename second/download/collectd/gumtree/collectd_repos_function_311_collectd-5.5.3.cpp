static int cpu_stage (size_t cpu_num, size_t state, derive_t value, cdtime_t now) /* {{{ */
{
	int status;
	cpu_state_t *s;
	value_t v;

	if (state >= COLLECTD_CPU_STATE_ACTIVE)
		return (EINVAL);

	status = cpu_states_alloc (cpu_num);
	if (status != 0)
		return (status);

	if (global_cpu_num <= cpu_num)
		global_cpu_num = cpu_num + 1;

	s = get_cpu_state (cpu_num, state);

	v.gauge = NAN;
	status = value_to_rate (&v, value, &s->conv, DS_TYPE_DERIVE, now);
	if (status != 0)
		return (status);

	s->rate = v.gauge;
	s->has_value = 1;
	return (0);
}