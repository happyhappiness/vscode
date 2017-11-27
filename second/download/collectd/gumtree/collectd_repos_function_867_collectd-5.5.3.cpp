static void
free_all_buffers(void)
{
	allocated = 0;
	initialized = 0;

	CPU_FREE(cpu_present_set);
	cpu_present_set = NULL;
	cpu_present_set = 0;

	CPU_FREE(cpu_affinity_set);
	cpu_affinity_set = NULL;
	cpu_affinity_setsize = 0;

	CPU_FREE(cpu_saved_affinity_set);
	cpu_saved_affinity_set = NULL;
	cpu_saved_affinity_setsize = 0;

	free(thread_even);
	free(core_even);
	free(package_even);

	thread_even = NULL;
	core_even = NULL;
	package_even = NULL;

	free(thread_odd);
	free(core_odd);
	free(package_odd);

	thread_odd = NULL;
	core_odd = NULL;
	package_odd = NULL;

	free(thread_delta);
	free(core_delta);
	free(package_delta);

	thread_delta = NULL;
	core_delta = NULL;
	package_delta = NULL;
}