static int
update_max_cpu_id(unsigned int cpu)
{
	if (topology.max_cpu_id < cpu)
		topology.max_cpu_id = cpu;
	return 0;
}