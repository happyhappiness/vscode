static void unlink_base_data(struct base_data *c)
{
	struct base_data *base = c->base;
	if (base)
		base->child = NULL;
	else
		get_thread_data()->base_cache = NULL;
	free_base_data(c);
}