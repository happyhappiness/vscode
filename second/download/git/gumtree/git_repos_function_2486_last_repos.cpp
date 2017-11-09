static struct dir_entry *dir_add_name(struct dir_struct *dir,
				      struct index_state *istate,
				      const char *pathname, int len)
{
	if (index_file_exists(istate, pathname, len, ignore_case))
		return NULL;

	ALLOC_GROW(dir->entries, dir->nr+1, dir->alloc);
	return dir->entries[dir->nr++] = dir_entry_new(pathname, len);
}