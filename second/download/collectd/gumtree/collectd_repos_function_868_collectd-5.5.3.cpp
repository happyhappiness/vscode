static int setup_all_buffers(void)
{
	int ret;

	DO_OR_GOTO_ERR(topology_probe());
	DO_OR_GOTO_ERR(allocate_counters(&thread_even, &core_even, &package_even));
	DO_OR_GOTO_ERR(allocate_counters(&thread_odd, &core_odd, &package_odd));
	DO_OR_GOTO_ERR(allocate_counters(&thread_delta, &core_delta, &package_delta));
	initialize_counters();
	DO_OR_GOTO_ERR(for_all_cpus(set_temperature_target, EVEN_COUNTERS));
	DO_OR_GOTO_ERR(for_all_cpus(set_temperature_target, ODD_COUNTERS));

	allocated = 1;
	return 0;
err:
	free_all_buffers();
	return ret;
}