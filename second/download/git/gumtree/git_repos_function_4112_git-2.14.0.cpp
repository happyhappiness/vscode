int test_lazy_init_name_hash(struct index_state *istate, int try_threaded)
{
	lazy_nr_dir_threads = 0;
	lazy_try_threaded = try_threaded;

	lazy_init_name_hash(istate);

	return lazy_nr_dir_threads;
}