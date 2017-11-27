static void cpu_commit_one (int cpu_num, /* {{{ */
		gauge_t rates[static COLLECTD_CPU_STATE_MAX])
{
	size_t state;
	gauge_t sum;

	sum = rates[COLLECTD_CPU_STATE_ACTIVE];
	RATE_ADD (sum, rates[COLLECTD_CPU_STATE_IDLE]);

	if (!report_by_state)
	{
		gauge_t percent = 100.0 * rates[COLLECTD_CPU_STATE_ACTIVE] / sum;
		submit_percent (cpu_num, COLLECTD_CPU_STATE_ACTIVE, percent);
		return;
	}

	for (state = 0; state < COLLECTD_CPU_STATE_ACTIVE; state++)
	{
		gauge_t percent = 100.0 * rates[state] / sum;
		submit_percent (cpu_num, state, percent);
	}
}