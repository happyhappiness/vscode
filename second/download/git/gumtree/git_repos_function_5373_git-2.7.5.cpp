static int refresh(struct refresh_params *o, unsigned int flag)
{
	setup_work_tree();
	read_cache_preload(NULL);
	*o->has_errors |= refresh_cache(o->flags | flag);
	return 0;
}