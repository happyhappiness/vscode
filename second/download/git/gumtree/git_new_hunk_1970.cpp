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
