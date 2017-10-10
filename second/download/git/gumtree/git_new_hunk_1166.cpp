		die_errno(_("failed to stat '%s'"), path);
	if (!(S_ISREG(st.st_mode) || S_ISLNK(st.st_mode)))
		die(_("'%s': not a regular file or symlink"), path);

	diff_set_mnemonic_prefix(&revs->diffopt, "o/", "w/");

	if (blob[0]->mode == S_IFINVALID)
		blob[0]->mode = canon_mode(st.st_mode);

	stuff_change(&revs->diffopt,
		     blob[0]->mode, canon_mode(st.st_mode),
		     &blob[0]->item->oid, &null_oid,
		     1, 0,
		     blob[0]->path ? blob[0]->path : path,
		     path);
	diffcore_std(&revs->diffopt);
	diff_flush(&revs->diffopt);
	return 0;
}

static int builtin_diff_blobs(struct rev_info *revs,
			      int argc, const char **argv,
			      struct object_array_entry **blob)
{
	unsigned mode = canon_mode(S_IFREG | 0644);

	if (argc > 1)
		usage(builtin_diff_usage);

	if (blob[0]->mode == S_IFINVALID)
		blob[0]->mode = mode;

	if (blob[1]->mode == S_IFINVALID)
		blob[1]->mode = mode;

	stuff_change(&revs->diffopt,
		     blob[0]->mode, blob[1]->mode,
		     &blob[0]->item->oid, &blob[1]->item->oid,
		     1, 1,
		     blob_path(blob[0]), blob_path(blob[1]));
	diffcore_std(&revs->diffopt);
	diff_flush(&revs->diffopt);
	return 0;
}

static int builtin_diff_index(struct rev_info *revs,
