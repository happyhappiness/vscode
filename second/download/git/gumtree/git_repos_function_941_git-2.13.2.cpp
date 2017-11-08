int run_processes_parallel(int n,
			   get_next_task_fn get_next_task,
			   start_failure_fn start_failure,
			   task_finished_fn task_finished,
			   void *pp_cb)
{
	int i, code;
	int output_timeout = 100;
	int spawn_cap = 4;
	struct parallel_processes pp;

	pp_init(&pp, n, get_next_task, start_failure, task_finished, pp_cb);
	while (1) {
		for (i = 0;
		    i < spawn_cap && !pp.shutdown &&
		    pp.nr_processes < pp.max_processes;
		    i++) {
			code = pp_start_one(&pp);
			if (!code)
				continue;
			if (code < 0) {
				pp.shutdown = 1;
				kill_children(&pp, -code);
			}
			break;
		}
		if (!pp.nr_processes)
			break;
		pp_buffer_stderr(&pp, output_timeout);
		pp_output(&pp);
		code = pp_collect_finished(&pp);
		if (code) {
			pp.shutdown = 1;
			if (code < 0)
				kill_children(&pp, -code);
		}
	}

	pp_cleanup(&pp);
	return 0;
}