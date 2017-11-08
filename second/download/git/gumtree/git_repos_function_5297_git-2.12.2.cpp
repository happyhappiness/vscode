static struct base_data *alloc_base_data(void)
{
	struct base_data *base = xcalloc(1, sizeof(struct base_data));
	base->ref_last = -1;
	base->ofs_last = -1;
	return base;
}