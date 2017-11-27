static void sig_usr1_handler (int signal)
{
	pthread_t      thread;
	pthread_attr_t attr;

	/* flushing the data might take a while,
	 * so it should be done asynchronously */
	pthread_attr_init (&attr);
	pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
	pthread_create (&thread, &attr, do_flush, NULL);
}