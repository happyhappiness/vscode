static int lookup_lazy_params(struct index_state *istate)
{
	int nr_cpus;

	lazy_nr_dir_threads = 0;

	if (!lazy_try_threaded)
		return 0;

	/*
	 * If we are respecting case, just use the original
	 * code to build the "istate->name_hash".  We don't
	 * need the complexity here.
	 */
	if (!ignore_case)
		return 0;

	nr_cpus = online_cpus();
	if (nr_cpus < 2)
		return 0;

	if (istate->cache_nr < 2 * LAZY_THREAD_COST)
		return 0;

	if (istate->cache_nr < nr_cpus * LAZY_THREAD_COST)
		nr_cpus = istate->cache_nr / LAZY_THREAD_COST;
	lazy_nr_dir_threads = nr_cpus;
	return lazy_nr_dir_threads;
}