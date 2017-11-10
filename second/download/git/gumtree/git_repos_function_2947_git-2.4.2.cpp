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

	remove_file(o, 1, a->path, would_lose_untracked(a->path));
	remove_file(o, 1, b->path, would_lose_untracked(b->path));

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