static void copy_templates(const char *template_dir)
{
	struct strbuf path = STRBUF_INIT;
	struct strbuf template_path = STRBUF_INIT;
	size_t template_len;
	struct repository_format template_format;
	struct strbuf err = STRBUF_INIT;
	DIR *dir;
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

	strbuf_addstr(&template_path, template_dir);
	strbuf_complete(&template_path, '/');
	template_len = template_path.len;

	dir = opendir(template_path.buf);
	if (!dir) {
		warning(_("templates not found %s"), template_dir);
		goto free_return;
	}

	/* Make sure that template is from the correct vintage */
	strbuf_addstr(&template_path, "config");
	read_repository_format(&template_format, template_path.buf);
	strbuf_setlen(&template_path, template_len);

	/*
	 * No mention of version at all is OK, but anything else should be
	 * verified.
	 */
	if (template_format.version >= 0 &&
	    verify_repository_format(&template_format, &err) < 0) {
		warning(_("not copying templates from '%s': %s"),
			  template_dir, err.buf);
		strbuf_release(&err);
		goto close_free_return;
	}

	strbuf_addstr(&path, get_git_common_dir());
	strbuf_complete(&path, '/');
	copy_templates_1(&path, &template_path, dir);
close_free_return:
	closedir(dir);
free_return:
	free(to_free);
	strbuf_release(&path);
	strbuf_release(&template_path);
}