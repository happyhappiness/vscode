void repo_config(struct repository *repo, config_fn_t fn, void *data)
{
	git_config_check_init(repo);
	configset_iter(repo->config, fn, data);
}