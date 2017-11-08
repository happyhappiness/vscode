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
		return update_stages(o, dest->path, NULL,
				     rename_branch == o->branch1 ? dest : NULL,
				     rename_branch == o->branch1 ? NULL : dest);
}