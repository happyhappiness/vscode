static int ce_excluded(struct dir_struct *dir, const struct cache_entry *ce)
{
	int dtype = ce_to_dtype(ce);
	return is_excluded(dir, ce->name, &dtype);
}