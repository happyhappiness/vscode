	return -1;
}

int finish_async(struct async *async)
{
#ifdef NO_PTHREADS
	return wait_or_whine(async->pid, "child process", 0);
#else
	void *ret = (void *)(intptr_t)(-1);

	if (pthread_join(async->tid, &ret))
		error("pthread_join failed");
	return (int)(intptr_t)ret;
