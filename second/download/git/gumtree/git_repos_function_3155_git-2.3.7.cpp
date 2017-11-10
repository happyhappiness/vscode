static int tloop_spawnwait_tasks(struct bidirectional_transfer_state *s)
{
	pid_t pid1, pid2;
	int ret = 0;

	/* Fork thread #1: git to program. */
	pid1 = fork();
	if (pid1 < 0)
		die_errno("Can't start thread for copying data");
	else if (pid1 == 0) {
		udt_kill_transfer(&s->ptg);
		exit(udt_copy_task_routine(&s->gtp) ? 0 : 1);
	}

	/* Fork thread #2: program to git. */
	pid2 = fork();
	if (pid2 < 0)
		die_errno("Can't start thread for copying data");
	else if (pid2 == 0) {
		udt_kill_transfer(&s->gtp);
		exit(udt_copy_task_routine(&s->ptg) ? 0 : 1);
	}

	/*
	 * Close both streams in parent as to not interfere with
	 * end of file detection and wait for both tasks to finish.
	 */
	udt_kill_transfer(&s->gtp);
	udt_kill_transfer(&s->ptg);
	ret |= tloop_join(pid1, "Git to program copy");
	ret |= tloop_join(pid2, "Program to git copy");
	return ret;
}