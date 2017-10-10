}

int cmd_commit_tree(int argc, const char **argv, const char *prefix)
{
	int i, got_tree = 0;
	struct commit_list *parents = NULL;
	unsigned char tree_sha1[20];
	unsigned char commit_sha1[20];
	struct strbuf buffer = STRBUF_INIT;

	git_config(commit_tree_config, NULL);

	if (argc < 2 || !strcmp(argv[1], "-h"))
		usage(commit_tree_usage);

	for (i = 1; i < argc; i++) {
		const char *arg = argv[i];
		if (!strcmp(arg, "-p")) {
			unsigned char sha1[20];
			if (argc <= ++i)
				usage(commit_tree_usage);
			if (get_sha1_commit(argv[i], sha1))
				die("Not a valid object name %s", argv[i]);
			assert_sha1_type(sha1, OBJ_COMMIT);
			new_parent(lookup_commit(sha1), &parents);
			continue;
		}

		if (skip_prefix(arg, "-S", &sign_commit))
			continue;

