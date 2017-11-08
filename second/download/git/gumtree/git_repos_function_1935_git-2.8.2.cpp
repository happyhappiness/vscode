static int check_repo_format(const char *var, const char *value, void *cb)
{
	const char *ext;

	if (strcmp(var, "core.repositoryformatversion") == 0)
		repository_format_version = git_config_int(var, value);
	else if (strcmp(var, "core.sharedrepository") == 0)
		shared_repository = git_config_perm(var, value);
	else if (skip_prefix(var, "extensions.", &ext)) {
		/*
		 * record any known extensions here; otherwise,
		 * we fall through to recording it as unknown, and
		 * check_repository_format will complain
		 */
		if (!strcmp(ext, "noop"))
			;
		else if (!strcmp(ext, "preciousobjects"))
			repository_format_precious_objects = git_config_bool(var, value);
		else
			string_list_append(&unknown_extensions, ext);
	}
	return 0;
}