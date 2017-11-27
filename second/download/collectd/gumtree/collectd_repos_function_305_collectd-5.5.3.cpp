static cpu_state_t *get_cpu_state (size_t cpu_num, size_t state) /* {{{ */
{
	size_t index = ((cpu_num * COLLECTD_CPU_STATE_MAX) + state);

	if (index >= cpu_states_num)
		return (NULL);

	return (&cpu_states[index]);
}