{
	int clean_merge = 1;
	int normalize = o->renormalize;
	unsigned o_mode = entry->stages[1].mode;
	unsigned a_mode = entry->stages[2].mode;
	unsigned b_mode = entry->stages[3].mode;
	unsigned char *o_sha = stage_sha(entry->stages[1].sha, o_mode);
	unsigned char *a_sha = stage_sha(entry->stages[2].sha, a_mode);
	unsigned char *b_sha = stage_sha(entry->stages[3].sha, b_mode);

	entry->processed = 1;
	if (entry->rename_conflict_info) {
		struct rename_conflict_info *conflict_info = entry->rename_conflict_info;
		switch (conflict_info->rename_type) {
		case RENAME_NORMAL:
		case RENAME_ONE_FILE_TO_ONE:
			clean_merge = merge_content(o, path,
						    o_sha, o_mode, a_sha, a_mode, b_sha, b_mode,
						    conflict_info);
			break;
		case RENAME_DELETE:
			clean_merge = 0;
			conflict_rename_delete(o, conflict_info->pair1,
					       conflict_info->branch1,
					       conflict_info->branch2);
			break;
		case RENAME_ONE_FILE_TO_TWO:
			clean_merge = 0;
			conflict_rename_rename_1to2(o, conflict_info);
			break;
		case RENAME_TWO_FILES_TO_ONE:
			clean_merge = 0;
			conflict_rename_rename_2to1(o, conflict_info);
			break;
		default:
			entry->processed = 0;
			break;
		}
	} else if (o_sha && (!a_sha || !b_sha)) {
		/* Case A: Deleted in one */
		if ((!a_sha && !b_sha) ||
		    (!b_sha && blob_unchanged(o_sha, o_mode, a_sha, a_mode, normalize, path)) ||
		    (!a_sha && blob_unchanged(o_sha, o_mode, b_sha, b_mode, normalize, path))) {
			/* Deleted in both or deleted in one and
			 * unchanged in the other */
			if (a_sha)
				output(o, 2, _("Removing %s"), path);
			/* do not touch working file if it did not exist */
			remove_file(o, 1, path, !a_sha);
		} else {
			/* Modify/delete; deleted side may have put a directory in the way */
			clean_merge = 0;
			handle_modify_delete(o, path, o_sha, o_mode,
					     a_sha, a_mode, b_sha, b_mode);
		}
	} else if ((!o_sha && a_sha && !b_sha) ||
		   (!o_sha && !a_sha && b_sha)) {
		/* Case B: Added in one. */
		/* [nothing|directory] -> ([nothing|directory], file) */

		const char *add_branch;
		const char *other_branch;
		unsigned mode;
		const unsigned char *sha;
		const char *conf;

		if (a_sha) {
			add_branch = o->branch1;
			other_branch = o->branch2;
			mode = a_mode;
			sha = a_sha;
			conf = _("file/directory");
		} else {
			add_branch = o->branch2;
			other_branch = o->branch1;
			mode = b_mode;
			sha = b_sha;
			conf = _("directory/file");
		}
		if (dir_in_way(path, !o->call_depth)) {
			char *new_path = unique_path(o, path, add_branch);
			clean_merge = 0;
			output(o, 1, _("CONFLICT (%s): There is a directory with name %s in %s. "
			       "Adding %s as %s"),
			       conf, path, other_branch, path, new_path);
			update_file(o, 0, sha, mode, new_path);
			if (o->call_depth)
				remove_file_from_cache(path);
			free(new_path);
		} else {
			output(o, 2, _("Adding %s"), path);
			/* do not overwrite file if already present */
			update_file_flags(o, sha, mode, path, 1, !a_sha);
		}
	} else if (a_sha && b_sha) {
		/* Case C: Added in both (check for same permissions) and */
		/* case D: Modified in both, but differently. */
		clean_merge = merge_content(o, path,
					    o_sha, o_mode, a_sha, a_mode, b_sha, b_mode,
					    NULL);
	} else if (!o_sha && !a_sha && !b_sha) {
		/*
		 * this entry was deleted altogether. a_mode == 0 means
		 * we had that path and want to actively remove it.
		 */
		remove_file(o, 1, path, !a_mode);
	} else
		die(_("Fatal merge failure, shouldn't happen."));

	return clean_merge;
}

int merge_trees(struct merge_options *o,
		struct tree *head,
