
	string_list_clear(&needs_pushing, 0);

	return ret;
}

static int append_oid_to_array(const char *ref, const struct object_id *oid,
			       int flags, void *data)
{
	struct oid_array *array = data;
	oid_array_append(array, oid);
	return 0;
}

void check_for_new_submodule_commits(struct object_id *oid)
{
	if (!initialized_fetch_ref_tips) {
		for_each_ref(append_oid_to_array, &ref_tips_before_fetch);
		initialized_fetch_ref_tips = 1;
	}

	oid_array_append(&ref_tips_after_fetch, oid);
}

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

int submodule_touches_in_range(struct object_id *excl_oid,
			       struct object_id *incl_oid)
{
	struct string_list subs = STRING_LIST_INIT_DUP;
	struct argv_array args = ARGV_ARRAY_INIT;
	int ret;

	gitmodules_config();
	/* No need to check if there are no submodules configured */
	if (!submodule_from_path(NULL, NULL))
		return 0;

	argv_array_push(&args, "--"); /* args[0] program name */
	argv_array_push(&args, oid_to_hex(incl_oid));
	argv_array_push(&args, "--not");
	argv_array_push(&args, oid_to_hex(excl_oid));

	collect_changed_submodules(&subs, &args);
	ret = subs.nr;

	argv_array_clear(&args);

	free_submodules_oids(&subs);
	return ret;
}

struct submodule_parallel_fetch {
	int count;
	struct argv_array args;
	const char *work_tree;
	const char *prefix;
	int command_line_option;
