}

static NORETURN void die_async(const char *err, va_list params)
{
	vreportf("fatal: ", err, params);

	if (in_async()) {
		struct async *async = pthread_getspecific(async_key);
		if (async->proc_in >= 0)
			close(async->proc_in);
		if (async->proc_out >= 0)
			close(async->proc_out);
		pthread_exit((void *)128);
