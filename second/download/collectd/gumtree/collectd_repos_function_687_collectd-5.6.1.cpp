static void ps_submit_proc_list (procstat_t *ps)
{
	value_t values[2];
	value_list_t vl = VALUE_LIST_INIT;

	vl.values = values;
	vl.values_len = 2;
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "processes", sizeof (vl.plugin));
	sstrncpy (vl.plugin_instance, ps->name, sizeof (vl.plugin_instance));

	sstrncpy (vl.type, "ps_vm", sizeof (vl.type));
	vl.values[0].gauge = ps->vmem_size;
	vl.values_len = 1;
	plugin_dispatch_values (&vl);

	sstrncpy (vl.type, "ps_rss", sizeof (vl.type));
	vl.values[0].gauge = ps->vmem_rss;
	vl.values_len = 1;
	plugin_dispatch_values (&vl);

	sstrncpy (vl.type, "ps_data", sizeof (vl.type));
	vl.values[0].gauge = ps->vmem_data;
	vl.values_len = 1;
	plugin_dispatch_values (&vl);

	sstrncpy (vl.type, "ps_code", sizeof (vl.type));
	vl.values[0].gauge = ps->vmem_code;
	vl.values_len = 1;
	plugin_dispatch_values (&vl);

	sstrncpy (vl.type, "ps_stacksize", sizeof (vl.type));
	vl.values[0].gauge = ps->stack_size;
	vl.values_len = 1;
	plugin_dispatch_values (&vl);

	sstrncpy (vl.type, "ps_cputime", sizeof (vl.type));
	vl.values[0].derive = ps->cpu_user_counter;
	vl.values[1].derive = ps->cpu_system_counter;
	vl.values_len = 2;
	plugin_dispatch_values (&vl);

	sstrncpy (vl.type, "ps_count", sizeof (vl.type));
	vl.values[0].gauge = ps->num_proc;
	vl.values[1].gauge = ps->num_lwp;
	vl.values_len = 2;
	plugin_dispatch_values (&vl);

	sstrncpy (vl.type, "ps_pagefaults", sizeof (vl.type));
	vl.values[0].derive = ps->vmem_minflt_counter;
	vl.values[1].derive = ps->vmem_majflt_counter;
	vl.values_len = 2;
	plugin_dispatch_values (&vl);

	if ( (ps->io_rchar != -1) && (ps->io_wchar != -1) )
	{
		sstrncpy (vl.type, "ps_disk_octets", sizeof (vl.type));
		vl.values[0].derive = ps->io_rchar;
		vl.values[1].derive = ps->io_wchar;
		vl.values_len = 2;
		plugin_dispatch_values (&vl);
	}

	if ( (ps->io_syscr != -1) && (ps->io_syscw != -1) )
	{
		sstrncpy (vl.type, "ps_disk_ops", sizeof (vl.type));
		vl.values[0].derive = ps->io_syscr;
		vl.values[1].derive = ps->io_syscw;
		vl.values_len = 2;
		plugin_dispatch_values (&vl);
	}

	if ( report_ctx_switch )
	{
		sstrncpy (vl.type, "contextswitch", sizeof (vl.type));
		sstrncpy (vl.type_instance, "voluntary", sizeof (vl.type_instance));
		vl.values[0].derive = ps->cswitch_vol;
		vl.values_len = 1;
		plugin_dispatch_values (&vl);

		sstrncpy (vl.type, "contextswitch", sizeof (vl.type));
		sstrncpy (vl.type_instance, "involuntary", sizeof (vl.type_instance));
		vl.values[0].derive = ps->cswitch_invol;
		vl.values_len = 1;
		plugin_dispatch_values (&vl);
	}

	DEBUG ("name = %s; num_proc = %lu; num_lwp = %lu; "
			"vmem_size = %lu; vmem_rss = %lu; vmem_data = %lu; "
			"vmem_code = %lu; "
			"vmem_minflt_counter = %"PRIi64"; vmem_majflt_counter = %"PRIi64"; "
			"cpu_user_counter = %"PRIi64"; cpu_system_counter = %"PRIi64"; "
			"io_rchar = %"PRIi64"; io_wchar = %"PRIi64"; "
			"io_syscr = %"PRIi64"; io_syscw = %"PRIi64"; "
			"cswitch_vol = %"PRIi64"; cswitch_invol = %"PRIi64";",
			ps->name, ps->num_proc, ps->num_lwp,
			ps->vmem_size, ps->vmem_rss,
			ps->vmem_data, ps->vmem_code,
			ps->vmem_minflt_counter, ps->vmem_majflt_counter,
			ps->cpu_user_counter, ps->cpu_system_counter,
			ps->io_rchar, ps->io_wchar, ps->io_syscr, ps->io_syscw,
			ps->cswitch_vol, ps->cswitch_invol);
}