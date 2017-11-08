static void show_other_files(struct dir_struct *dir)
{
	int i;

	for (i = 0; i < dir->nr; i++) {
		struct dir_entry *ent = dir->entries[i];
		if (!cache_name_is_other(ent->name, ent->len))
			continue;
		show_dir_entry(tag_other, ent);
	}
}