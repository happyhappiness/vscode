{
	int clean_merge = 1;
	int normalize = o->renormalize;
	unsigned o_mode = entry->stages[1].mode;
	unsigned a_mode = entry->stages[2].mode;
	unsigned b_mode = entry->stages[3].mode;
	struct object_id *o_oid = stage_oid(&entry->stages[1].oid, o_mode);
	struct object_id *a_oid = stage_oid(&entry->stages[2].oid, a_mode);
	struct object_id *b_oid = stage_oid(&entry->stages[3].oid, b_mode);

	entry->processed = 1;
	if (entry->rename_conflict_info) {
		struct rename_conflict_info *conflict_info = entry->rename_conflict_info;
		switch (conflict_info->rename_type) {
		case RENAME_NORMAL:
		case RENAME_ONE_FILE_TO_ONE:
			clean_merge = merge_content(o, path,
						    o_oid, o_mode, a_oid, a_mode, b_oid, b_mode,
						    conflict_info);
			break;
		case RENAME_DELETE:
			clean_merge = 0;
			if (conflict_rename_delete(o,
						   conflict_info->pair1,
						   conflict_info->branch1,
						   conflict_info->branch2))
				clean_merge = -1;
			break;
		case RENAME_ONE_FILE_TO_TWO:
			clean_merge = 0;
			if (conflict_rename_rename_1to2(o, conflict_info))
				clean_merge = -1;
			break;
		case RENAME_TWO_FILES_TO_ONE:
			clean_merge = 0;
			if (conflict_rename_rename_2to1(o, conflict_info))
				clean_merge = -1;
			break;
		default:
			entry->processed = 0;
			break;
		}
	} else if (o_oid && (!a_oid || !b_oid)) {
		/* Case A: Deleted in one */
		if ((!a_oid && !b_oid) ||
		    (!b_oid && blob_unchanged(o, o_oid, o_mode, a_oid, a_mode, normalize, path)) ||
		    (!a_oid && blob_unchanged(o, o_oid, o_mode, b_oid, b_mode, normalize, path))) {
			/* Deleted in both or deleted in one and
			 * unchanged in the other */
			if (a_oid)
				output(o, 2, _("Removing %s"), path);
			/* do not touch working file if it did not exist */
			remove_file(o, 1, path, !a_oid);
		} else {
			/* Modify/delete; deleted side may have put a directory in the way */
			clean_merge = 0;
			if (handle_modify_delete(o, path, o_oid, o_mode,
						 a_oid, a_mode, b_oid, b_mode))
				clean_merge = -1;
		}
	} else if ((!o_oid && a_oid && !b_oid) ||
		   (!o_oid && !a_oid && b_oid)) {
		/* Case B: Added in one. */
		/* [nothing|directory] -> ([nothing|directory], file) */

		const char *add_branch;
		const char *other_branch;
		unsigned mode;
		const struct object_id *oid;
		const char *conf;

		if (a_oid) {
			add_branch = o->branch1;
			other_branch = o->branch2;
			mode = a_mode;
			oid = a_oid;
			conf = _("file/directory");
		} else {
			add_branch = o->branch2;
			other_branch = o->branch1;
			mode = b_mode;
			oid = b_oid;
			conf = _("directory/file");
		}
		if (dir_in_way(path, !o->call_depth)) {
			char *new_path = unique_path(o, path, add_branch);
			clean_merge = 0;
			output(o, 1, _("CONFLICT (%s): There is a directory with name %s in %s. "
			       "Adding %s as %s"),
			       conf, path, other_branch, path, new_path);
			if (update_file(o, 0, oid, mode, new_path))
				clean_merge = -1;
			else if (o->call_depth)
				remove_file_from_cache(path);
			free(new_path);
		} else {
			output(o, 2, _("Adding %s"), path);
			/* do not overwrite file if already present */
			if (update_file_flags(o, oid, mode, path, 1, !a_oid))
				clean_merge = -1;
		}
	} else if (a_oid && b_oid) {
		/* Case C: Added in both (check for same permissions) and */
		/* case D: Modified in both, but differently. */
		clean_merge = merge_content(o, path,
					    o_oid, o_mode, a_oid, a_mode, b_oid, b_mode,
					    NULL);
	} else if (!o_oid && !a_oid && !b_oid) {
		/*
		 * this entry was deleted altogether. a_mode == 0 means
		 * we had that path and want to actively remove it.
		 */
		remove_file(o, 1, path, !a_mode);
	} else
		die("BUG: fatal merge failure, shouldn't happen.");

	return clean_merge;
}

int merge_trees(struct merge_options *o,
		struct tree *head,
