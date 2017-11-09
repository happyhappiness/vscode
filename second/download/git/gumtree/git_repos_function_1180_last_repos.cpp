static void preload_index(struct index_state *index,
			  const struct pathspec *pathspec)
{
	int threads, i, work, offset;
	struct thread_data data[MAX_PARALLEL];

	if (!core_preload_index)
		return;

	threads = index->cache_nr / THREAD_COST;
	if (threads < 2)
		return;
	if (threads > MAX_PARALLEL)
		threads = MAX_PARALLEL;
	offset = 0;
	work = DIV_ROUND_UP(index->cache_nr, threads);
	memset(&data, 0, sizeof(data));
	for (i = 0; i < threads; i++) {
		struct thread_data *p = data+i;
		p->index = index;
		if (pathspec)
			copy_pathspec(&p->pathspec, pathspec);
		p->offset = offset;
		p->nr = work;
		offset += work;
		if (pthread_create(&p->pthread, NULL, preload_thread, p))
			die("unable to create threaded lstat");
	}
	for (i = 0; i < threads; i++) {
		struct thread_data *p = data+i;
		if (pthread_join(p->pthread, NULL))
			die("unable to join threaded lstat");
	}
}