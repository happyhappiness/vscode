	if (!git_configset_get_value(cs, key, &value))
		return git_config_pathname(dest, key, value);
	else
		return 1;
}

/* Functions use to read configuration from a repository */
static void repo_read_config(struct repository *repo)
{
	struct config_options opts;

	opts.respect_includes = 1;
	opts.commondir = repo->commondir;
	opts.git_dir = repo->gitdir;

	if (!repo->config)
		repo->config = xcalloc(1, sizeof(struct config_set));
	else
		git_configset_clear(repo->config);

	git_configset_init(repo->config);

	if (config_with_options(config_set_callback, repo->config, NULL, &opts) < 0)
		/*
		 * config_with_options() normally returns only
		 * zero, as most errors are fatal, and
		 * non-fatal potential errors are guarded by "if"
		 * statements that are entered only when no error is
		 * possible.
		 *
		 * If we ever encounter a non-fatal error, it means
		 * something went really wrong and we should stop
		 * immediately.
		 */
		die(_("unknown error occurred while reading the configuration files"));
}

static void git_config_check_init(struct repository *repo)
{
	if (repo->config && repo->config->hash_initialized)
		return;
	repo_read_config(repo);
}

static void repo_config_clear(struct repository *repo)
{
	if (!repo->config || !repo->config->hash_initialized)
		return;
	git_configset_clear(repo->config);
}

void repo_config(struct repository *repo, config_fn_t fn, void *data)
{
	git_config_check_init(repo);
	configset_iter(repo->config, fn, data);
}

int repo_config_get_value(struct repository *repo,
			  const char *key, const char **value)
{
	git_config_check_init(repo);
	return git_configset_get_value(repo->config, key, value);
}

const struct string_list *repo_config_get_value_multi(struct repository *repo,
						      const char *key)
{
	git_config_check_init(repo);
	return git_configset_get_value_multi(repo->config, key);
}

int repo_config_get_string_const(struct repository *repo,
				 const char *key, const char **dest)
{
	int ret;
	git_config_check_init(repo);
	ret = git_configset_get_string_const(repo->config, key, dest);
	if (ret < 0)
		git_die_config(key, NULL);
	return ret;
}

int repo_config_get_string(struct repository *repo,
			   const char *key, char **dest)
{
	git_config_check_init(repo);
	return repo_config_get_string_const(repo, key, (const char **)dest);
}

int repo_config_get_int(struct repository *repo,
			const char *key, int *dest)
{
	git_config_check_init(repo);
	return git_configset_get_int(repo->config, key, dest);
}

int repo_config_get_ulong(struct repository *repo,
			  const char *key, unsigned long *dest)
{
	git_config_check_init(repo);
	return git_configset_get_ulong(repo->config, key, dest);
}

int repo_config_get_bool(struct repository *repo,
			 const char *key, int *dest)
{
	git_config_check_init(repo);
	return git_configset_get_bool(repo->config, key, dest);
}

int repo_config_get_bool_or_int(struct repository *repo,
				const char *key, int *is_bool, int *dest)
{
	git_config_check_init(repo);
	return git_configset_get_bool_or_int(repo->config, key, is_bool, dest);
}

int repo_config_get_maybe_bool(struct repository *repo,
			       const char *key, int *dest)
{
	git_config_check_init(repo);
	return git_configset_get_maybe_bool(repo->config, key, dest);
}

int repo_config_get_pathname(struct repository *repo,
			     const char *key, const char **dest)
{
	int ret;
	git_config_check_init(repo);
	ret = git_configset_get_pathname(repo->config, key, dest);
	if (ret < 0)
		git_die_config(key, NULL);
	return ret;
}

/* Functions used historically to read configuration from 'the_repository' */
void git_config(config_fn_t fn, void *data)
{
	repo_config(the_repository, fn, data);
}

void git_config_clear(void)
{
	repo_config_clear(the_repository);
}

int git_config_get_value(const char *key, const char **value)
{
	return repo_config_get_value(the_repository, key, value);
}

const struct string_list *git_config_get_value_multi(const char *key)
{
	return repo_config_get_value_multi(the_repository, key);
}

int git_config_get_string_const(const char *key, const char **dest)
{
	return repo_config_get_string_const(the_repository, key, dest);
}

int git_config_get_string(const char *key, char **dest)
{
	return repo_config_get_string(the_repository, key, dest);
}

int git_config_get_int(const char *key, int *dest)
{
	return repo_config_get_int(the_repository, key, dest);
}

int git_config_get_ulong(const char *key, unsigned long *dest)
{
	return repo_config_get_ulong(the_repository, key, dest);
}

int git_config_get_bool(const char *key, int *dest)
{
	return repo_config_get_bool(the_repository, key, dest);
}

int git_config_get_bool_or_int(const char *key, int *is_bool, int *dest)
{
	return repo_config_get_bool_or_int(the_repository, key, is_bool, dest);
}

int git_config_get_maybe_bool(const char *key, int *dest)
{
	return repo_config_get_maybe_bool(the_repository, key, dest);
}

int git_config_get_pathname(const char *key, const char **dest)
{
	return repo_config_get_pathname(the_repository, key, dest);
}

int git_config_get_expiry(const char *key, const char **output)
{
	int ret = git_config_get_string_const(key, output);
	if (ret)
		return ret;
	if (strcmp(*output, "now")) {
		timestamp_t now = approxidate("now");
		if (approxidate(*output) >= now)
			git_die_config(key, _("Invalid %s: '%s'"), key, *output);
	}
	return ret;
}

