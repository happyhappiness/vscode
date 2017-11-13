int merge_trees(struct merge_options *o,
		struct tree *head,
		struct tree *merge,
		struct tree *common,
		struct tree **result)
{
	int code, clean;

	if (o->subtree_shift) {
		merge = shift_tree_object(head, merge, o->subtree_shift);
		common = shift_tree_object(head, common, o->subtree_shift);
	}

	if (sha_eq(common->object.sha1, merge->object.sha1)) {
		output(o, 0, _("Already up-to-date!"));
		*result = head;
		return 1;
	}

	code = git_merge_trees(o->call_depth, common, head, merge);

	if (code != 0) {
		if (show(o, 4) || o->call_depth)
			die(_("merging of trees %s and %s failed"),
			    sha1_to_hex(head->object.sha1),
			    sha1_to_hex(merge->object.sha1));
		else
			exit(128);
	}

	if (unmerged_cache()) {
		struct string_list *entries, *re_head, *re_merge;
		int i;
		string_list_clear(&o->current_file_set, 1);
		string_list_clear(&o->current_directory_set, 1);
		get_files_dirs(o, head);
		get_files_dirs(o, merge);

		entries = get_unmerged();
		record_df_conflict_files(o, entries);
		re_head  = get_renames(o, head, common, head, merge, entries);
		re_merge = get_renames(o, merge, common, head, merge, entries);
		clean = process_renames(o, re_head, re_merge);
		for (i = entries->nr-1; 0 <= i; i--) {
			const char *path = entries->items[i].string;
			struct stage_data *e = entries->items[i].util;
			if (!e->processed
				&& !process_entry(o, path, e))
				clean = 0;
		}
		for (i = 0; i < entries->nr; i++) {
			struct stage_data *e = entries->items[i].util;
			if (!e->processed)
				die(_("Unprocessed path??? %s"),
				    entries->items[i].string);
		}

		string_list_clear(re_merge, 0);
		string_list_clear(re_head, 0);
		string_list_clear(entries, 1);

		free(re_merge);
		free(re_head);
		free(entries);
	}
	else
		clean = 1;

	if (o->call_depth)
		*result = write_tree_from_memory(o);

	return clean;
}