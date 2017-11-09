static int merge_content(struct merge_options *o,
			 const char *path,
			 struct object_id *o_oid, int o_mode,
			 struct object_id *a_oid, int a_mode,
			 struct object_id *b_oid, int b_mode,
			 struct rename_conflict_info *rename_conflict_info)
{
	const char *reason = _("content");
	const char *path1 = NULL, *path2 = NULL;
	struct merge_file_info mfi;
	struct diff_filespec one, a, b;
	unsigned df_conflict_remains = 0;

	if (!o_oid) {
		reason = _("add/add");
		o_oid = (struct object_id *)&null_oid;
	}
	one.path = a.path = b.path = (char *)path;
	oidcpy(&one.oid, o_oid);
	one.mode = o_mode;
	oidcpy(&a.oid, a_oid);
	a.mode = a_mode;
	oidcpy(&b.oid, b_oid);
	b.mode = b_mode;

	if (rename_conflict_info) {
		struct diff_filepair *pair1 = rename_conflict_info->pair1;

		path1 = (o->branch1 == rename_conflict_info->branch1) ?
			pair1->two->path : pair1->one->path;
		/* If rename_conflict_info->pair2 != NULL, we are in
		 * RENAME_ONE_FILE_TO_ONE case.  Otherwise, we have a
		 * normal rename.
		 */
		path2 = (rename_conflict_info->pair2 ||
			 o->branch2 == rename_conflict_info->branch1) ?
			pair1->two->path : pair1->one->path;

		if (dir_in_way(path, !o->call_depth,
			       S_ISGITLINK(pair1->two->mode)))
			df_conflict_remains = 1;
	}
	if (merge_file_special_markers(o, &one, &a, &b,
				       o->branch1, path1,
				       o->branch2, path2, &mfi))
		return -1;

	if (mfi.clean && !df_conflict_remains &&
	    oid_eq(&mfi.oid, a_oid) && mfi.mode == a_mode) {
		int path_renamed_outside_HEAD;
		output(o, 3, _("Skipped %s (merged same as existing)"), path);
		/*
		 * The content merge resulted in the same file contents we
		 * already had.  We can return early if those file contents
		 * are recorded at the correct path (which may not be true
		 * if the merge involves a rename).
		 */
		path_renamed_outside_HEAD = !path2 || !strcmp(path, path2);
		if (!path_renamed_outside_HEAD) {
			add_cacheinfo(o, mfi.mode, &mfi.oid, path,
				      0, (!o->call_depth), 0);
			return mfi.clean;
		}
	} else
		output(o, 2, _("Auto-merging %s"), path);

	if (!mfi.clean) {
		if (S_ISGITLINK(mfi.mode))
			reason = _("submodule");
		output(o, 1, _("CONFLICT (%s): Merge conflict in %s"),
				reason, path);
		if (rename_conflict_info && !df_conflict_remains)
			if (update_stages(o, path, &one, &a, &b))
				return -1;
	}

	if (df_conflict_remains) {
		char *new_path;
		if (o->call_depth) {
			remove_file_from_cache(path);
		} else {
			if (!mfi.clean) {
				if (update_stages(o, path, &one, &a, &b))
					return -1;
			} else {
				int file_from_stage2 = was_tracked(path);
				struct diff_filespec merged;
				oidcpy(&merged.oid, &mfi.oid);
				merged.mode = mfi.mode;

				if (update_stages(o, path, NULL,
						  file_from_stage2 ? &merged : NULL,
						  file_from_stage2 ? NULL : &merged))
					return -1;
			}

		}
		new_path = unique_path(o, path, rename_conflict_info->branch1);
		output(o, 1, _("Adding as %s instead"), new_path);
		if (update_file(o, 0, &mfi.oid, mfi.mode, new_path)) {
			free(new_path);
			return -1;
		}
		free(new_path);
		mfi.clean = 0;
	} else if (update_file(o, mfi.clean, &mfi.oid, mfi.mode, path))
		return -1;
	return mfi.clean;
}