static struct ref_dir *get_ref_dir(struct ref_entry *entry)
{
	struct ref_dir *dir;
	assert(entry->flag & REF_DIR);
	dir = &entry->u.subdir;
	if (entry->flag & REF_INCOMPLETE) {
		read_loose_refs(entry->name, dir);

		/*
		 * Manually add refs/bisect, which, being
		 * per-worktree, might not appear in the directory
		 * listing for refs/ in the main repo.
		 */
		if (!strcmp(entry->name, "refs/")) {
			int pos = search_ref_dir(dir, "refs/bisect/", 12);
			if (pos < 0) {
				struct ref_entry *child_entry;
				child_entry = create_dir_entry(dir->ref_store,
							       "refs/bisect/",
							       12, 1);
				add_entry_to_dir(dir, child_entry);
				read_loose_refs("refs/bisect",
						&child_entry->u.subdir);
			}
		}
		entry->flag &= ~REF_INCOMPLETE;
	}
	return dir;
}