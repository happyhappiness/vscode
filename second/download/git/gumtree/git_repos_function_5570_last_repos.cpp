static void free_base_data(struct base_data *c)
{
	if (c->data) {
		FREE_AND_NULL(c->data);
		get_thread_data()->base_cache_used -= c->size;
	}
}