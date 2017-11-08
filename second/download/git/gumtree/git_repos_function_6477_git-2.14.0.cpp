static void clear_ref_dir(struct ref_dir *dir)
{
	int i;
	for (i = 0; i < dir->nr; i++)
		free_ref_entry(dir->entries[i]);
	FREE_AND_NULL(dir->entries);
	dir->sorted = dir->nr = dir->alloc = 0;
}