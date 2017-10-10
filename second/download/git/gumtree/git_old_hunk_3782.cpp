			 o->branch2 == rename_conflict_info->branch1) ?
			pair1->two->path : pair1->one->path;

		if (dir_in_way(path, !o->call_depth))
			df_conflict_remains = 1;
	}
	mfi = merge_file_special_markers(o, &one, &a, &b,
					 o->branch1, path1,
					 o->branch2, path2);

	if (mfi.clean && !df_conflict_remains &&
	    sha_eq(mfi.sha, a_sha) && mfi.mode == a_mode) {
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
			add_cacheinfo(mfi.mode, mfi.sha, path,
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
			update_stages(path, &one, &a, &b);
	}

	if (df_conflict_remains) {
		char *new_path;
		if (o->call_depth) {
			remove_file_from_cache(path);
		} else {
			if (!mfi.clean)
				update_stages(path, &one, &a, &b);
			else {
				int file_from_stage2 = was_tracked(path);
				struct diff_filespec merged;
				hashcpy(merged.sha1, mfi.sha);
				merged.mode = mfi.mode;

				update_stages(path, NULL,
					      file_from_stage2 ? &merged : NULL,
					      file_from_stage2 ? NULL : &merged);
			}

		}
		new_path = unique_path(o, path, rename_conflict_info->branch1);
		output(o, 1, _("Adding as %s instead"), new_path);
		update_file(o, 0, mfi.sha, mfi.mode, new_path);
		free(new_path);
		mfi.clean = 0;
	} else {
		update_file(o, mfi.clean, mfi.sha, mfi.mode, path);
	}
	return mfi.clean;

}

/* Per entry merge function */
static int process_entry(struct merge_options *o,
			 const char *path, struct stage_data *entry)
{
