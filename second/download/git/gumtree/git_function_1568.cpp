int git_config_early(config_fn_t fn, void *data, const char *repo_config)
{
	int ret = 0, found = 0;
	char *xdg_config = NULL;
	char *user_config = NULL;

	home_config_paths(&user_config, &xdg_config, "config");

	if (git_config_system() && !access_or_die(git_etc_gitconfig(), R_OK, 0)) {
		ret += git_config_from_file(fn, git_etc_gitconfig(),
					    data);
		found += 1;
	}

	if (xdg_config && !access_or_die(xdg_config, R_OK, ACCESS_EACCES_OK)) {
		ret += git_config_from_file(fn, xdg_config, data);
		found += 1;
	}

	if (user_config && !access_or_die(user_config, R_OK, ACCESS_EACCES_OK)) {
		ret += git_config_from_file(fn, user_config, data);
		found += 1;
	}

	if (repo_config && !access_or_die(repo_config, R_OK, 0)) {
		ret += git_config_from_file(fn, repo_config, data);
		found += 1;
	}

	switch (git_config_from_parameters(fn, data)) {
	case -1: /* error */
		die("unable to parse command-line config");
		break;
	case 0: /* found nothing */
		break;
	default: /* found at least one item */
		found++;
		break;
	}

	free(xdg_config);
	free(user_config);
	return ret == 0 ? found : ret;
}