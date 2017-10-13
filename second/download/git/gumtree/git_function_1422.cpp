int find_unpushed_submodules(struct oid_array *commits,
		const char *remotes_name, struct string_list *needs_pushing)
{
	struct rev_info rev;
	struct commit *commit;
	struct string_list submodules = STRING_LIST_INIT_DUP;
	struct string_list_item *submodule;
	struct argv_array argv = ARGV_ARRAY_INIT;

	init_revisions(&rev, NULL);

	/* argv.argv[0] will be ignored by setup_revisions */
	argv_array_push(&argv, "find_unpushed_submodules");
	oid_array_for_each_unique(commits, append_oid_to_argv, &argv);
	argv_array_push(&argv, "--not");
	argv_array_pushf(&argv, "--remotes=%s", remotes_name);

	setup_revisions(argv.argc, argv.argv, &rev, NULL);
	if (prepare_revision_walk(&rev))
		die("revision walk setup failed");

	while ((commit = get_revision(&rev)) != NULL)
		find_unpushed_submodule_commits(commit, &submodules);

	reset_revision_walk();
	argv_array_clear(&argv);

	for_each_string_list_item(submodule, &submodules) {
		struct oid_array *commits = (struct oid_array *) submodule->util;

		if (submodule_needs_pushing(submodule->string, commits))
			string_list_insert(needs_pushing, submodule->string);
	}
	free_submodules_sha1s(&submodules);

	return needs_pushing->nr;
}