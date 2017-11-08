static void copy_templates_1(struct strbuf *path, struct strbuf *template,
			     DIR *dir)
{
	size_t path_baselen = path->len;
	size_t template_baselen = template->len;
	struct dirent *de;

	/* Note: if ".git/hooks" file exists in the repository being
	 * re-initialized, /etc/core-git/templates/hooks/update would
	 * cause "git init" to fail here.  I think this is sane but
	 * it means that the set of templates we ship by default, along
	 * with the way the namespace under .git/ is organized, should
	 * be really carefully chosen.
	 */
	safe_create_dir(path->buf, 1);
	while ((de = readdir(dir)) != NULL) {
		struct stat st_git, st_template;
		int exists = 0;

		strbuf_setlen(path, path_baselen);
		strbuf_setlen(template, template_baselen);

		if (de->d_name[0] == '.')
			continue;
		strbuf_addstr(path, de->d_name);
		strbuf_addstr(template, de->d_name);
		if (lstat(path->buf, &st_git)) {
			if (errno != ENOENT)
				die_errno(_("cannot stat '%s'"), path->buf);
		}
		else
			exists = 1;

		if (lstat(template->buf, &st_template))
			die_errno(_("cannot stat template '%s'"), template->buf);

		if (S_ISDIR(st_template.st_mode)) {
			DIR *subdir = opendir(template->buf);
			if (!subdir)
				die_errno(_("cannot opendir '%s'"), template->buf);
			strbuf_addch(path, '/');
			strbuf_addch(template, '/');
			copy_templates_1(path, template, subdir);
			closedir(subdir);
		}
		else if (exists)
			continue;
		else if (S_ISLNK(st_template.st_mode)) {
			struct strbuf lnk = STRBUF_INIT;
			if (strbuf_readlink(&lnk, template->buf, 0) < 0)
				die_errno(_("cannot readlink '%s'"), template->buf);
			if (symlink(lnk.buf, path->buf))
				die_errno(_("cannot symlink '%s' '%s'"),
					  lnk.buf, path->buf);
			strbuf_release(&lnk);
		}
		else if (S_ISREG(st_template.st_mode)) {
			if (copy_file(path->buf, template->buf, st_template.st_mode))
				die_errno(_("cannot copy '%s' to '%s'"),
					  template->buf, path->buf);
		}
		else
			error(_("ignoring template %s"), template->buf);
	}
}