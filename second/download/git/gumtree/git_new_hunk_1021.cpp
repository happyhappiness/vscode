	oidcpy(&b.oid, b_oid);
	b.mode = b_mode;
	return merge_file_1(o, &one, &a, &b, branch1, branch2, mfi);
}

static int handle_change_delete(struct merge_options *o,
				 const char *path, const char *old_path,
				 const struct object_id *o_oid, int o_mode,
				 const struct object_id *changed_oid,
				 int changed_mode,
				 const char *change_branch,
				 const char *delete_branch,
				 const char *change, const char *change_past)
{
	char *alt_path = NULL;
	const char *update_path = path;
	int ret = 0;

	if (dir_in_way(path, !o->call_depth, 0)) {
		update_path = alt_path = unique_path(o, path, change_branch);
	}

	if (o->call_depth) {
		/*
		 * We cannot arbitrarily accept either a_sha or b_sha as
		 * correct; since there is no true "middle point" between
		 * them, simply reuse the base version for virtual merge base.
		 */
		ret = remove_file_from_cache(path);
		if (!ret)
			ret = update_file(o, 0, o_oid, o_mode, update_path);
	} else {
		if (!alt_path) {
			if (!old_path) {
				output(o, 1, _("CONFLICT (%s/delete): %s deleted in %s "
				       "and %s in %s. Version %s of %s left in tree."),
				       change, path, delete_branch, change_past,
				       change_branch, change_branch, path);
			} else {
				output(o, 1, _("CONFLICT (%s/delete): %s deleted in %s "
				       "and %s to %s in %s. Version %s of %s left in tree."),
				       change, old_path, delete_branch, change_past, path,
				       change_branch, change_branch, path);
			}
		} else {
			if (!old_path) {
				output(o, 1, _("CONFLICT (%s/delete): %s deleted in %s "
				       "and %s in %s. Version %s of %s left in tree at %s."),
				       change, path, delete_branch, change_past,
				       change_branch, change_branch, path, alt_path);
			} else {
				output(o, 1, _("CONFLICT (%s/delete): %s deleted in %s "
				       "and %s to %s in %s. Version %s of %s left in tree at %s."),
				       change, old_path, delete_branch, change_past, path,
				       change_branch, change_branch, path, alt_path);
			}
		}
		/*
		 * No need to call update_file() on path when change_branch ==
		 * o->branch1 && !alt_path, since that would needlessly touch
		 * path.  We could call update_file_flags() with update_cache=0
		 * and update_wd=0, but that's a no-op.
		 */
		if (change_branch != o->branch1 || alt_path)
			ret = update_file(o, 0, changed_oid, changed_mode, update_path);
	}
	free(alt_path);

	return ret;
}

static int conflict_rename_delete(struct merge_options *o,
				   struct diff_filepair *pair,
				   const char *rename_branch,
				   const char *delete_branch)
{
	const struct diff_filespec *orig = pair->one;
	const struct diff_filespec *dest = pair->two;

	if (handle_change_delete(o,
				 o->call_depth ? orig->path : dest->path,
				 o->call_depth ? NULL : orig->path,
				 &orig->oid, orig->mode,
				 &dest->oid, dest->mode,
				 rename_branch, delete_branch,
				 _("rename"), _("renamed")))
		return -1;

	if (o->call_depth)
		return remove_file_from_cache(dest->path);
	else
