void git_config(config_fn_t fn, void *data)
{
	repo_config(the_repository, fn, data);
}