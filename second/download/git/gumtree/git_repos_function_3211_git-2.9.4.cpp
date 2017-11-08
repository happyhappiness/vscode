static void conflict_rename_rename_1to2(struct merge_options *o,
					struct rename_conflict_info *ci)
{
	/* One file was renamed in both branches, but to different names. */
	struct diff_filespec *one = ci->pair1->one;
	struct diff_filespec *a = ci->pair1->two;
	struct diff_filespec *b = ci->pair2->two;

	output(o, 1, _("CONFLICT (rename/rename): "
	       "Rename \"%s\"->\"%s\" in branch \"%s\" "
	       "rename \"%s\"->\"%s\" in \"%s\"%s"),
	       one->path, a->path, ci->branch1,
	       one->path, b->path, ci->branch2,
	       o->call_depth ? _(" (left unresolved)") : "");
	if (o->call_depth) {
		struct merge_file_info mfi;
		struct diff_filespec other;
		struct diff_filespec *add;
		mfi = merge_file_one(o, one->path,
				 one->sha1, one->mode,
				 a->sha1, a->mode,
				 b->sha1, b->mode,
				 ci->branch1, ci->branch2);
		/*
		 * FIXME: For rename/add-source conflicts (if we could detect
		 * such), this is wrong.  We should instead find a unique
		 * pathname and then either rename the add-source file to that
		 * unique path, or use that unique path instead of src here.
		 */
		update_file(o, 0, mfi.sha, mfi.mode, one->path);

		/*
		 * Above, we put the merged content at the merge-base's
		 * path.  Now we usually need to delete both a->path and
		 * b->path.  However, the rename on each side of the merge
		 * could also be involved in a rename/add conflict.  In
		 * such cases, we should keep the added file around,
		 * resolving the conflict at that path in its favor.
		 */
		add = filespec_from_entry(&other, ci->dst_entry1, 2 ^ 1);
		if (add)
			update_file(o, 0, add->sha1, add->mode, a->path);
		else
			remove_file_from_cache(a->path);
		add = filespec_from_entry(&other, ci->dst_entry2, 3 ^ 1);
		if (add)
			update_file(o, 0, add->sha1, add->mode, b->path);
		else
			remove_file_from_cache(b->path);
	} else {
		handle_file(o, a, 2, ci);
		handle_file(o, b, 3, ci);
	}
}