static void cpu_commit_without_aggregation (void) /* {{{ */
{
	for (int state = 0; state < COLLECTD_CPU_STATE_ACTIVE; state++)
	{
		for (size_t cpu_num = 0; cpu_num < global_cpu_num; cpu_num++)
		{
			cpu_state_t *s = get_cpu_state (cpu_num, state);

			if (!s->has_value)
				continue;

			submit_derive ((int) cpu_num, (int) state, s->conv.last_value.derive);
		}
	}
}