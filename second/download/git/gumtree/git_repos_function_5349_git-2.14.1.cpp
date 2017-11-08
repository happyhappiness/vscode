static int ce_excluded(struct dir_struct *dir, struct index_state *istate,
		       const char *fullname, const struct cache_entry *ce)
{
	int dtype = ce_to_dtype(ce);
	return is_excluded(dir, istate, fullname, &dtype);
}