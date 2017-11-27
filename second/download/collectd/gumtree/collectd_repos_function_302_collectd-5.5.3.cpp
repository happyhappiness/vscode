static void submit_percent(int cpu_num, int cpu_state, gauge_t percent)
{
	value_t value;

	/* This function is called for all known CPU states, but each read
	 * method will only report a subset. The remaining states are left as
	 * NAN and we ignore them here. */
	if (isnan (percent))
		return;

	value.gauge = percent;
	submit_value (cpu_num, cpu_state, "percent", value);
}