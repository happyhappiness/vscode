static void ps_submit_proc_list (procstat_t *ps)
{
	value_t values[2];
	value_list_t vl = VALUE_LIST_INIT;

	vl.values = values;
	vl.values_len = 2;
	vl.time = time (NULL);
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "processes", sizeof (vl.plugin));
	sstrncpy (vl.plugin_instance, ps->name, sizeof (vl.plugin_instance));

	sstrncpy (vl.type, "ps_rss", sizeof (vl.type));
	vl.values[0].gauge = ps->vmem_rss;
	vl.values_len = 1;
	plugin_dispatch_values (&vl);

	sstrncpy (vl.type, "ps_cputime", sizeof (vl.type));
	vl.values[0].counter = ps->cpu_user_counter;
	vl.values[1].counter = ps->cpu_system_counter;
	vl.values_len = 2;
	plugin_dispatch_values (&vl);

	sstrncpy (vl.type, "ps_count", sizeof (vl.type));
	vl.values[0].gauge = ps->num_proc;
	vl.values[1].gauge = ps->num_lwp;
	vl.values_len = 2;
	plugin_dispatch_values (&vl);

	sstrncpy (vl.type, "ps_pagefaults", sizeof (vl.type));
	vl.values[0].counter = ps->vmem_minflt_counter;
	vl.values[1].counter = ps->vmem_majflt_counter;
	vl.values_len = 2;
	plugin_dispatch_values (&vl);

	DEBUG ("name = %s; num_proc = %lu; num_lwp = %lu; vmem_rss = %lu; "
			"vmem_minflt_counter = %lu; vmem_majflt_counter = %lu; "
			"cpu_user_counter = %lu; cpu_system_counter = %lu;",
			ps->name, ps->num_proc, ps->num_lwp, ps->vmem_rss,
			ps->vmem_minflt_counter, ps->vmem_majflt_counter,
		       	ps->cpu_user_counter, ps->cpu_system_counter);
}