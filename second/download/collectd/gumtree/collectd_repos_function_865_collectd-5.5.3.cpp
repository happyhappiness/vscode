static void
init_counter(struct thread_data *thread_base, struct core_data *core_base,
	struct pkg_data *pkg_base, unsigned int cpu_id)
{
	struct thread_data *t;
	struct core_data *c;
	struct pkg_data *p;
	struct cpu_topology *cpu = &topology.cpus[cpu_id];

	t = GET_THREAD(thread_base, !(cpu->first_thread_in_core), cpu->core_id, cpu->package_id);
	c = GET_CORE(core_base, cpu->core_id, cpu->package_id);
	p = GET_PKG(pkg_base, cpu->package_id);

	t->cpu_id = cpu_id;
	if (cpu->first_thread_in_core)
		t->flags |= CPU_IS_FIRST_THREAD_IN_CORE;
	if (cpu->first_core_in_package)
		t->flags |= CPU_IS_FIRST_CORE_IN_PACKAGE;

	c->core_id = cpu->core_id;
	p->package_id = cpu->package_id;
}