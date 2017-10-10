	 * The textconv interface is intimately tied to diff_filespecs, so we
	 * have to pretend to be one. If we could unify the grep_source
	 * and diff_filespec structs, this mess could just go away.
	 */
	df = alloc_filespec(gs->path);
	switch (gs->type) {
	case GREP_SOURCE_SHA1:
		fill_filespec(df, gs->identifier, 1, 0100644);
		break;
	case GREP_SOURCE_FILE:
		fill_filespec(df, null_sha1, 0, 0100644);
		break;
	default:
		die("BUG: attempt to textconv something without a path?");
	}

	/*
