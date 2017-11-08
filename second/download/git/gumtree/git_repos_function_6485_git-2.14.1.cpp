struct ref_entry *find_ref_entry(struct ref_dir *dir, const char *refname)
{
	int entry_index;
	struct ref_entry *entry;
	dir = find_containing_dir(dir, refname, 0);
	if (!dir)
		return NULL;
	entry_index = search_ref_dir(dir, refname, strlen(refname));
	if (entry_index == -1)
		return NULL;
	entry = dir->entries[entry_index];
	return (entry->flag & REF_DIR) ? NULL : entry;
}