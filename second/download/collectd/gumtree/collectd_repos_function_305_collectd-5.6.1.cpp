static int cpu_states_alloc (size_t cpu_num) /* {{{ */
{
	cpu_state_t *tmp;
	size_t sz;

	sz = (((size_t) cpu_num) + 1) * COLLECTD_CPU_STATE_MAX;
	assert (sz > 0);

	/* We already have enough space. */
	if (cpu_states_num >= sz)
		return 0;

	tmp = realloc (cpu_states, sz * sizeof (*cpu_states));
	if (tmp == NULL)
	{
		ERROR ("cpu plugin: realloc failed.");
		return (ENOMEM);
	}
	cpu_states = tmp;
	tmp = cpu_states + cpu_states_num;

	memset (tmp, 0, (sz - cpu_states_num) * sizeof (*cpu_states));
	cpu_states_num = sz;
	return 0;
}