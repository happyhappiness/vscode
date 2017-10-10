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

static void conflict_rename_rename_2to1(struct merge_options *o,
					struct rename_conflict_info *ci)
{
	/* Two files, a & b, were renamed to the same thing, c. */
	struct diff_filespec *a = ci->pair1->one;
	struct diff_filespec *b = ci->pair2->one;
	struct diff_filespec *c1 = ci->pair1->two;
	struct diff_filespec *c2 = ci->pair2->two;
	char *path = c1->path; /* == c2->path */
	struct merge_file_info mfi_c1;
	struct merge_file_info mfi_c2;

	output(o, 1, _("CONFLICT (rename/rename): "
	       "Rename %s->%s in %s. "
	       "Rename %s->%s in %s"),
	       a->path, c1->path, ci->branch1,
	       b->path, c2->path, ci->branch2);

	remove_file(o, 1, a->path, o->call_depth || would_lose_untracked(a->path));
	remove_file(o, 1, b->path, o->call_depth || would_lose_untracked(b->path));

	mfi_c1 = merge_file_special_markers(o, a, c1, &ci->ren1_other,
					    o->branch1, c1->path,
					    o->branch2, ci->ren1_other.path);
	mfi_c2 = merge_file_special_markers(o, b, &ci->ren2_other, c2,
					    o->branch1, ci->ren2_other.path,
					    o->branch2, c2->path);

	if (o->call_depth) {
		/*
		 * If mfi_c1.clean && mfi_c2.clean, then it might make
		 * sense to do a two-way merge of those results.  But, I
		 * think in all cases, it makes sense to have the virtual
		 * merge base just undo the renames; they can be detected
		 * again later for the non-recursive merge.
		 */
		remove_file(o, 0, path, 0);
		update_file(o, 0, mfi_c1.sha, mfi_c1.mode, a->path);
		update_file(o, 0, mfi_c2.sha, mfi_c2.mode, b->path);
	} else {
		char *new_path1 = unique_path(o, path, ci->branch1);
		char *new_path2 = unique_path(o, path, ci->branch2);
		output(o, 1, _("Renaming %s to %s and %s to %s instead"),
		       a->path, new_path1, b->path, new_path2);
		remove_file(o, 0, path, 0);
		update_file(o, 0, mfi_c1.sha, mfi_c1.mode, new_path1);
		update_file(o, 0, mfi_c2.sha, mfi_c2.mode, new_path2);
		free(new_path2);
		free(new_path1);
	}
}

static int process_renames(struct merge_options *o,
			   struct string_list *a_renames,
			   struct string_list *b_renames)
{
