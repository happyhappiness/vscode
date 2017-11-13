static void copy_templates(const char *template_dir)
{
	char path[PATH_MAX];
	char template_path[PATH_MAX];
	int template_len;
	DIR *dir;
	const char *git_dir = get_git_dir();
	int len = strlen(git_dir);
	char *to_free = NULL;

	if (!template_dir)
		template_dir = getenv(TEMPLATE_DIR_ENVIRONMENT);
	if (!template_dir)
		template_dir = init_db_template_dir;
	if (!template_dir)
		template_dir = to_free = system_path(DEFAULT_GIT_TEMPLATE_DIR);
	if (!template_dir[0]) {
		free(to_free);
		return;
	}
	template_len = strlen(template_dir);
	if (PATH_MAX <= (template_len+strlen("/config")))
		die(_("insanely long template path %s"), template_dir);
	strcpy(template_path, template_dir);
	if (template_path[template_len-1] != '/') {
		template_path[template_len++] = '/';
		template_path[template_len] = 0;
	}
	dir = opendir(template_path);
	if (!dir) {
		warning(_("templates not found %s"), template_dir);
		goto free_return;
	}

	/* Make sure that template is from the correct vintage */
	strcpy(template_path + template_len, "config");
	repository_format_version = 0;
	git_config_from_file(check_repository_format_version,
			     template_path, NULL);
	template_path[template_len] = 0;

	if (repository_format_version &&
	    repository_format_version != GIT_REPO_VERSION) {
		warning(_("not copying templates of "
			"a wrong format version %d from '%s'"),
			repository_format_version,
			template_dir);
		goto close_free_return;
	}

	memcpy(path, git_dir, len);
	if (len && path[len - 1] != '/')
		path[len++] = '/';
	path[len] = 0;
	copy_templates_1(path, len,
			 template_path, template_len,
			 dir);
close_free_return:
	closedir(dir);
free_return:
	free(to_free);
}