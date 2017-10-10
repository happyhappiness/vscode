}

int cmd_commit_tree(int argc, const char **argv, const char *prefix)
{
	int i, got_tree = 0;
	struct commit_list *parents = NULL;
	struct object_id tree_oid;
	struct object_id commit_oid;
	struct strbuf buffer = STRBUF_INIT;

	git_config(commit_tree_config, NULL);

	if (argc < 2 || !strcmp(argv[1], "-h"))
		usage(commit_tree_usage);

	for (i = 1; i < argc; i++) {
		const char *arg = argv[i];
		if (!strcmp(arg, "-p")) {
			struct object_id oid;
			if (argc <= ++i)
				usage(commit_tree_usage);
			if (get_sha1_commit(argv[i], oid.hash))
				die("Not a valid object name %s", argv[i]);
			assert_sha1_type(oid.hash, OBJ_COMMIT);
			new_parent(lookup_commit(oid.hash), &parents);
			continue;
		}

		if (skip_prefix(arg, "-S", &sign_commit))
			continue;

