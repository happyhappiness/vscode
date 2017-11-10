static int tloop_spawnwait_tasks(struct bidirectional_transfer_state *s)
{
	pthread_t gtp_thread;
	pthread_t ptg_thread;
	int err;
	int ret = 0;
	err = pthread_create(&gtp_thread, NULL, udt_copy_task_routine,
		&s->gtp);
	if (err)
		die("Can't start thread for copying data: %s", strerror(err));
	err = pthread_create(&ptg_thread, NULL, udt_copy_task_routine,
		&s->ptg);
	if (err)
		die("Can't start thread for copying data: %s", strerror(err));

	ret |= tloop_join(gtp_thread, "Git to program copy");
	ret |= tloop_join(ptg_thread, "Program to git copy");
	return ret;
}