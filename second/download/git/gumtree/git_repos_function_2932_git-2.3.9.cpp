static void conflict_rename_delete(struct merge_options *o,
				   struct diff_filepair *pair,
				   const char *rename_branch,
				   const char *other_branch)
{
	const struct diff_filespec *orig = pair->one;
	const struct diff_filespec *dest = pair->two;
	const unsigned char *a_sha = NULL;
	const unsigned char *b_sha = NULL;
	int a_mode = 0;
	int b_mode = 0;

	if (rename_branch == o->branch1) {
		a_sha = dest->sha1;
		a_mode = dest->mode;
	} else {
		b_sha = dest->sha1;
		b_mode = dest->mode;
	}

	handle_change_delete(o,
			     o->call_depth ? orig->path : dest->path,
			     orig->sha1, orig->mode,
			     a_sha, a_mode,
			     b_sha, b_mode,
			     _("rename"), _("renamed"));

	if (o->call_depth) {
		remove_file_from_cache(dest->path);
	} else {
		update_stages(dest->path, NULL,
			      rename_branch == o->branch1 ? dest : NULL,
			      rename_branch == o->branch1 ? NULL : dest);
	}

}