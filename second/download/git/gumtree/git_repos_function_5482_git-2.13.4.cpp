static void prune_base_data(struct base_data *retain)
{
	struct base_data *b;
	struct thread_local *data = get_thread_data();
	for (b = data->base_cache;
	     data->base_cache_used > delta_base_cache_limit && b;
	     b = b->child) {
		if (b->data && b != retain)
			free_base_data(b);
	}
}