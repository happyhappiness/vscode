static void link_base_data(struct base_data *base, struct base_data *c)
{
	if (base)
		base->child = c;
	else
		get_thread_data()->base_cache = c;

	c->base = base;
	c->child = NULL;
	if (c->data)
		get_thread_data()->base_cache_used += c->size;
	prune_base_data(c);
}