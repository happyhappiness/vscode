static void calculate_changed_submodule_paths(void)
{
	struct argv_array argv = ARGV_ARRAY_INIT;
	struct string_list changed_submodules = STRING_LIST_INIT_DUP;
	const struct string_list_item *item;

	/* No need to check if there are no submodules configured */
	if (!submodule_from_path(NULL, NULL))
		return;

	argv_array_push(&argv, "--"); /* argv[0] program name */
	oid_array_for_each_unique(&ref_tips_after_fetch,
				   append_oid_to_argv, &argv);
	argv_array_push(&argv, "--not");
	oid_array_for_each_unique(&ref_tips_before_fetch,
				   append_oid_to_argv, &argv);

	/*
	 * Collect all submodules (whether checked out or not) for which new
	 * commits have been recorded upstream in "changed_submodule_paths".
	 */
	collect_changed_submodules(&changed_submodules, &argv);

	for_each_string_list_item(item, &changed_submodules) {
		struct oid_array *commits = item->util;
		const char *path = item->string;

		if (!submodule_has_commits(path, commits))
			string_list_append(&changed_submodule_paths, path);
	}

	free_submodules_oids(&changed_submodules);
	argv_array_clear(&argv);
	oid_array_clear(&ref_tips_before_fetch);
	oid_array_clear(&ref_tips_after_fetch);
	initialized_fetch_ref_tips = 0;
}