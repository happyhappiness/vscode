static void free_base_data(struct base_data *c)
{
	if (c->data) {
		free(c->data);
		c->data = NULL;
		get_thread_data()->base_cache_used -= c->size;
	}
}