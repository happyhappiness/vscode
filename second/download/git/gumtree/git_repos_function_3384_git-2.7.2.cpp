int index_dir_exists(struct index_state *istate, const char *name, int namelen)
{
	struct dir_entry *dir;

	lazy_init_name_hash(istate);
	dir = find_dir_entry(istate, name, namelen);
	return dir && dir->nr;
}