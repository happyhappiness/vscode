		opts->track = git_branch_track;

	if (new->name && !new->commit)
		die(_("Cannot switch branch to a non-commit '%s'"),
		    new->name);

	if (!new->commit && opts->new_branch) {
		unsigned char rev[20];
		int flag;

		if (!read_ref_full("HEAD", 0, rev, &flag) &&
		    (flag & REF_ISSYMREF) && is_null_sha1(rev))
