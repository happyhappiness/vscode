static void
initialize_counters(void)
{
	unsigned int cpu_id;

	for (cpu_id = 0; cpu_id <= topology.max_cpu_id; ++cpu_id) {
		if (cpu_is_not_present(cpu_id))
			continue;
		init_counter(EVEN_COUNTERS, cpu_id);
		init_counter(ODD_COUNTERS, cpu_id);
		init_counter(DELTA_COUNTERS, cpu_id);
	}
}