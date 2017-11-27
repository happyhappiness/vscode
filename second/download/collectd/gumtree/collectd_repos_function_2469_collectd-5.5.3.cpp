static _Bool check_drop_value (void) /* {{{ */
{
	static cdtime_t last_message_time = 0;
	static pthread_mutex_t last_message_lock = PTHREAD_MUTEX_INITIALIZER;

	double p;
	double q;
	int status;

	if (write_limit_high == 0)
		return (0);

	p = get_drop_probability ();
	if (p == 0.0)
		return (0);

	status = pthread_mutex_trylock (&last_message_lock);
	if (status == 0)
	{
		cdtime_t now;

		now = cdtime ();
		if ((now - last_message_time) > TIME_T_TO_CDTIME_T (1))
		{
			last_message_time = now;
			ERROR ("plugin_dispatch_values: Low water mark "
					"reached. Dropping %.0f%% of metrics.",
					100.0 * p);
		}
		pthread_mutex_unlock (&last_message_lock);
	}

	if (p == 1.0)
		return (1);

	q = cdrand_d ();
	if (q > p)
		return (1);
	else
		return (0);
}