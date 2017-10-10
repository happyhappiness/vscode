	ret = git_config_early(fn, data, repo_config);
	if (repo_config)
		free(repo_config);
	return ret;
}

int git_config(config_fn_t fn, void *data)
{
	return git_config_with_options(fn, data, NULL, 1);
}

/*
 * Find all the stuff for git_config_set() below.
 */

