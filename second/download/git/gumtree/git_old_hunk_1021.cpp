	oidcpy(&b.oid, b_oid);
	b.mode = b_mode;
	return merge_file_1(o, &one, &a, &b, branch1, branch2, mfi);
}

static int handle_change_delete(struct merge_options *o,
				 const char *path,
				 const struct object_id *o_oid, int o_mode,
				 const struct object_id *a_oid, int a_mode,
				 const struct object_id *b_oid, int b_mode,
				 const char *change, const char *change_past)
{
	char *renamed = NULL;
	int ret = 0;
	if (dir_in_way(path, !o->call_depth, 0)) {
		renamed = unique_path(o, path, a_oid ? o->branch1 : o->branch2);
	}

	if (o->call_depth) {
		/*
		 * We cannot arbitrarily accept either a_sha or b_sha as
		 * correct; since there is no true "middle point" between
		 * them, simply reuse the base version for virtual merge base.
		 */
		ret = remove_file_from_cache(path);
		if (!ret)
			ret = update_file(o, 0, o_oid, o_mode,
					  renamed ? renamed : path);
	} else if (!a_oid) {
		if (!renamed) {
			output(o, 1, _("CONFLICT (%s/delete): %s deleted in %s "
			       "and %s in %s. Version %s of %s left in tree."),
			       change, path, o->branch1, change_past,
			       o->branch2, o->branch2, path);
			ret = update_file(o, 0, b_oid, b_mode, path);
		} else {
			output(o, 1, _("CONFLICT (%s/delete): %s deleted in %s "
			       "and %s in %s. Version %s of %s left in tree at %s."),
			       change, path, o->branch1, change_past,
			       o->branch2, o->branch2, path, renamed);
			ret = update_file(o, 0, b_oid, b_mode, renamed);
		}
	} else {
		if (!renamed) {
			output(o, 1, _("CONFLICT (%s/delete): %s deleted in %s "
			       "and %s in %s. Version %s of %s left in tree."),
			       change, path, o->branch2, change_past,
			       o->branch1, o->branch1, path);
		} else {
			output(o, 1, _("CONFLICT (%s/delete): %s deleted in %s "
			       "and %s in %s. Version %s of %s left in tree at %s."),
			       change, path, o->branch2, change_past,
			       o->branch1, o->branch1, path, renamed);
			ret = update_file(o, 0, a_oid, a_mode, renamed);
		}
		/*
		 * No need to call update_file() on path when !renamed, since
		 * that would needlessly touch path.  We could call
		 * update_file_flags() with update_cache=0 and update_wd=0,
		 * but that's a no-op.
		 */
	}
	free(renamed);

	return ret;
}

static int conflict_rename_delete(struct merge_options *o,
				   struct diff_filepair *pair,
				   const char *rename_branch,
				   const char *other_branch)
{
	const struct diff_filespec *orig = pair->one;
	const struct diff_filespec *dest = pair->two;
	const struct object_id *a_oid = NULL;
	const struct object_id *b_oid = NULL;
	int a_mode = 0;
	int b_mode = 0;

	if (rename_branch == o->branch1) {
		a_oid = &dest->oid;
		a_mode = dest->mode;
	} else {
		b_oid = &dest->oid;
		b_mode = dest->mode;
	}

	if (handle_change_delete(o,
				 o->call_depth ? orig->path : dest->path,
				 &orig->oid, orig->mode,
				 a_oid, a_mode,
				 b_oid, b_mode,
				 _("rename"), _("renamed")))
		return -1;

	if (o->call_depth)
		return remove_file_from_cache(dest->path);
	else
