
static void *run_thread(void *data)
{
	struct async *async = data;
	intptr_t ret;

	pthread_setspecific(async_key, async);
	ret = async->proc(async->proc_in, async->proc_out, async->data);
	return (void *)ret;
}

static NORETURN void die_async(const char *err, va_list params)
