static void show_other_files(const struct index_state *istate,
			     const struct dir_struct *dir)
{
	int i;

	for (i = 0; i < dir->nr; i++) {
		struct dir_entry *ent = dir->entries[i];
		if (!index_name_is_other(istate, ent->name, ent->len))
			continue;
		show_dir_entry(tag_other, ent);
	}
}