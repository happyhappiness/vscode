static int check_repo_format(const char *var, const char *value, void *vdata)
{
	struct repository_format *data = vdata;
	const char *ext;

	if (strcmp(var, "core.repositoryformatversion") == 0)
		data->version = git_config_int(var, value);
	else if (skip_prefix(var, "extensions.", &ext)) {
		/*
		 * record any known extensions here; otherwise,
		 * we fall through to recording it as unknown, and
		 * check_repository_format will complain
		 */
		if (!strcmp(ext, "noop"))
			;
		else if (!strcmp(ext, "preciousobjects"))
			data->precious_objects = git_config_bool(var, value);
		else
			string_list_append(&data->unknown_extensions, ext);
	} else if (strcmp(var, "core.bare") == 0) {
		data->is_bare = git_config_bool(var, value);
	} else if (strcmp(var, "core.worktree") == 0) {
		if (!value)
			return config_error_nonbool(var);
		data->work_tree = xstrdup(value);
	}
	return 0;
}