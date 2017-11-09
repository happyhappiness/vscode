static int do_git_config_sequence(const struct config_options *opts,
				  config_fn_t fn, void *data)
{
	int ret = 0;
	char *xdg_config = xdg_config_home("config");
	char *user_config = expand_user_path("~/.gitconfig", 0);
	char *repo_config;

	if (opts->commondir)
		repo_config = mkpathdup("%s/config", opts->commondir);
	else
		repo_config = NULL;

	current_parsing_scope = CONFIG_SCOPE_SYSTEM;
	if (git_config_system() && !access_or_die(git_etc_gitconfig(), R_OK, 0))
		ret += git_config_from_file(fn, git_etc_gitconfig(),
					    data);

	current_parsing_scope = CONFIG_SCOPE_GLOBAL;
	if (xdg_config && !access_or_die(xdg_config, R_OK, ACCESS_EACCES_OK))
		ret += git_config_from_file(fn, xdg_config, data);

	if (user_config && !access_or_die(user_config, R_OK, ACCESS_EACCES_OK))
		ret += git_config_from_file(fn, user_config, data);

	current_parsing_scope = CONFIG_SCOPE_REPO;
	if (repo_config && !access_or_die(repo_config, R_OK, 0))
		ret += git_config_from_file(fn, repo_config, data);

	current_parsing_scope = CONFIG_SCOPE_CMDLINE;
	if (git_config_from_parameters(fn, data) < 0)
		die(_("unable to parse command-line config"));

	current_parsing_scope = CONFIG_SCOPE_UNKNOWN;
	free(xdg_config);
	free(user_config);
	free(repo_config);
	return ret;
}