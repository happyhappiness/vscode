static void aggregate (gauge_t *sum_by_state) /* {{{ */
{
	size_t cpu_num;
	size_t state;

	for (state = 0; state < COLLECTD_CPU_STATE_MAX; state++)
		sum_by_state[state] = NAN;

	for (cpu_num = 0; cpu_num < global_cpu_num; cpu_num++)
	{
		cpu_state_t *this_cpu_states = get_cpu_state (cpu_num, 0);

		this_cpu_states[COLLECTD_CPU_STATE_ACTIVE].rate = NAN;

		for (state = 0; state < COLLECTD_CPU_STATE_ACTIVE; state++)
		{
			if (!this_cpu_states[state].has_value)
				continue;

			RATE_ADD (sum_by_state[state], this_cpu_states[state].rate);
			if (state != COLLECTD_CPU_STATE_IDLE)
				RATE_ADD (this_cpu_states[COLLECTD_CPU_STATE_ACTIVE].rate, this_cpu_states[state].rate);
		}

		if (!isnan (this_cpu_states[COLLECTD_CPU_STATE_ACTIVE].rate))
			this_cpu_states[COLLECTD_CPU_STATE_ACTIVE].has_value = 1;

		RATE_ADD (sum_by_state[COLLECTD_CPU_STATE_ACTIVE], this_cpu_states[COLLECTD_CPU_STATE_ACTIVE].rate);
	}
}