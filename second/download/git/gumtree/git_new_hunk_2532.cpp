	struct commit_list *j;
	const char *filename;
	int fd;
	struct pretty_print_context ctx = {0};

	printf(_("Squash commit -- not updating HEAD\n"));
	filename = git_path_squash_msg();
	fd = open(filename, O_WRONLY | O_CREAT, 0666);
	if (fd < 0)
		die_errno(_("Could not write to '%s'"), filename);

	init_revisions(&rev, NULL);
	rev.ignore_merges = 1;
