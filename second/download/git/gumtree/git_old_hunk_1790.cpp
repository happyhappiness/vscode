	static const char *system_wide;
	if (!system_wide)
		system_wide = system_path(ETC_GITCONFIG);
	return system_wide;
}

int git_env_bool(const char *k, int def)
{
	const char *v = getenv(k);
	return v ? git_config_bool(k, v) : def;
}

int git_config_system(void)
{
	return !git_env_bool("GIT_CONFIG_NOSYSTEM", 0);
}

int git_config_early(config_fn_t fn, void *data, const char *repo_config)
