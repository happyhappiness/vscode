int get_shared_repository(void)
{
	if (need_shared_repository_from_config) {
		const char *var = "core.sharedrepository";
		const char *value;
		if (!git_config_get_value(var, &value))
			the_shared_repository = git_config_perm(var, value);
		need_shared_repository_from_config = 0;
	}
	return the_shared_repository;
}