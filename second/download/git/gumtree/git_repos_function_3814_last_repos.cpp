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
		return update_stages(o, dest->path, NULL,
				     rename_branch == o->branch1 ? dest : NULL,
				     rename_branch == o->branch1 ? NULL : dest);
}