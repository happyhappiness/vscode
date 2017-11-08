int is_submodule_active(struct repository *repo, const char *path)
{
	int ret = 0;
	char *key = NULL;
	char *value = NULL;
	const struct string_list *sl;
	const struct submodule *module;

	module = submodule_from_cache(repo, null_sha1, path);

	/* early return if there isn't a path->module mapping */
	if (!module)
		return 0;

	/* submodule.<name>.active is set */
	key = xstrfmt("submodule.%s.active", module->name);
	if (!repo_config_get_bool(repo, key, &ret)) {
		free(key);
		return ret;
	}
	free(key);

	/* submodule.active is set */
	sl = repo_config_get_value_multi(repo, "submodule.active");
	if (sl) {
		struct pathspec ps;
		struct argv_array args = ARGV_ARRAY_INIT;
		const struct string_list_item *item;

		for_each_string_list_item(item, sl) {
			argv_array_push(&args, item->string);
		}

		parse_pathspec(&ps, 0, 0, NULL, args.argv);
		ret = match_pathspec(&ps, path, strlen(path), 0, NULL, 1);

		argv_array_clear(&args);
		clear_pathspec(&ps);
		return ret;
	}

	/* fallback to checking if the URL is set */
	key = xstrfmt("submodule.%s.url", module->name);
	ret = !repo_config_get_string(repo, key, &value);

	free(value);
	free(key);
	return ret;
}