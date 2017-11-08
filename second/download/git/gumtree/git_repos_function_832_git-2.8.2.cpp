int in_async(void)
{
	if (!main_thread_set)
		return 0; /* no asyncs started yet */
	return !pthread_equal(main_thread, pthread_self());
}