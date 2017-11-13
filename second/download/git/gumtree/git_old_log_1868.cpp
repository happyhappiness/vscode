fprintf(stderr,
			_(
			"If you want to keep them by creating a new branch, "
			"this may be a good time\nto do so with:\n\n"
			" git branch <new-branch-name> %s\n\n"),
			find_unique_abbrev(commit->object.sha1, DEFAULT_ABBREV));