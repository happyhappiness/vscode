
static int init_is_bare_repository = 0;
static int init_shared_repository = -1;
static const char *init_db_template_dir;
static const char *git_link;

static void safe_create_dir(const char *dir, int share)
{
	if (mkdir(dir, 0777) < 0) {
		if (errno != EEXIST) {
			perror(dir);
			exit(1);
		}
	}
	else if (share && adjust_shared_perm(dir))
		die(_("Could not make %s writable by group"), dir);
}

static void copy_templates_1(char *path, int baselen,
			     char *template, int template_baselen,
			     DIR *dir)
{
	struct dirent *de;

	/* Note: if ".git/hooks" file exists in the repository being
	 * re-initialized, /etc/core-git/templates/hooks/update would
	 * cause "git init" to fail here.  I think this is sane but
	 * it means that the set of templates we ship by default, along
	 * with the way the namespace under .git/ is organized, should
	 * be really carefully chosen.
	 */
	safe_create_dir(path, 1);
	while ((de = readdir(dir)) != NULL) {
		struct stat st_git, st_template;
		int namelen;
		int exists = 0;

		if (de->d_name[0] == '.')
			continue;
		namelen = strlen(de->d_name);
		if ((PATH_MAX <= baselen + namelen) ||
		    (PATH_MAX <= template_baselen + namelen))
			die(_("insanely long template name %s"), de->d_name);
		memcpy(path + baselen, de->d_name, namelen+1);
		memcpy(template + template_baselen, de->d_name, namelen+1);
		if (lstat(path, &st_git)) {
			if (errno != ENOENT)
				die_errno(_("cannot stat '%s'"), path);
		}
		else
			exists = 1;

		if (lstat(template, &st_template))
			die_errno(_("cannot stat template '%s'"), template);

		if (S_ISDIR(st_template.st_mode)) {
			DIR *subdir = opendir(template);
			int baselen_sub = baselen + namelen;
			int template_baselen_sub = template_baselen + namelen;
			if (!subdir)
				die_errno(_("cannot opendir '%s'"), template);
			path[baselen_sub++] =
				template[template_baselen_sub++] = '/';
			path[baselen_sub] =
				template[template_baselen_sub] = 0;
			copy_templates_1(path, baselen_sub,
					 template, template_baselen_sub,
					 subdir);
			closedir(subdir);
		}
		else if (exists)
			continue;
		else if (S_ISLNK(st_template.st_mode)) {
			char lnk[256];
			int len;
			len = readlink(template, lnk, sizeof(lnk));
			if (len < 0)
				die_errno(_("cannot readlink '%s'"), template);
			if (sizeof(lnk) <= len)
				die(_("insanely long symlink %s"), template);
			lnk[len] = 0;
			if (symlink(lnk, path))
				die_errno(_("cannot symlink '%s' '%s'"), lnk, path);
		}
		else if (S_ISREG(st_template.st_mode)) {
			if (copy_file(path, template, st_template.st_mode))
				die_errno(_("cannot copy '%s' to '%s'"), template,
					  path);
		}
		else
			error(_("ignoring template %s"), template);
	}
}

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

static int git_init_db_config(const char *k, const char *v, void *cb)
{
	if (!strcmp(k, "init.templatedir"))
		return git_config_pathname(&init_db_template_dir, k, v);
