int git_config_system(void)
{
	return !git_env_bool("GIT_CONFIG_NOSYSTEM", 0);
}