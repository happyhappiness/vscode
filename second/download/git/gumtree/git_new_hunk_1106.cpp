		if (run_command(&cp))
			die(_("could not recurse into submodule '%s'"), path);

		strbuf_release(&sb);
	}
}

const char *get_superproject_working_tree(void)
{
	struct child_process cp = CHILD_PROCESS_INIT;
	struct strbuf sb = STRBUF_INIT;
	const char *one_up = real_path_if_valid("../");
	const char *cwd = xgetcwd();
	const char *ret = NULL;
	const char *subpath;
	int code;
	ssize_t len;

	if (!is_inside_work_tree())
		/*
		 * FIXME:
		 * We might have a superproject, but it is harder
		 * to determine.
		 */
		return NULL;

	if (!one_up)
		return NULL;

	subpath = relative_path(cwd, one_up, &sb);

	prepare_submodule_repo_env(&cp.env_array);
	argv_array_pop(&cp.env_array);

	argv_array_pushl(&cp.args, "--literal-pathspecs", "-C", "..",
			"ls-files", "-z", "--stage", "--full-name", "--",
			subpath, NULL);
	strbuf_reset(&sb);

	cp.no_stdin = 1;
	cp.no_stderr = 1;
	cp.out = -1;
	cp.git_cmd = 1;

	if (start_command(&cp))
		die(_("could not start ls-files in .."));

	len = strbuf_read(&sb, cp.out, PATH_MAX);
	close(cp.out);

	if (starts_with(sb.buf, "160000")) {
		int super_sub_len;
		int cwd_len = strlen(cwd);
		char *super_sub, *super_wt;

		/*
		 * There is a superproject having this repo as a submodule.
		 * The format is <mode> SP <hash> SP <stage> TAB <full name> \0,
		 * We're only interested in the name after the tab.
		 */
		super_sub = strchr(sb.buf, '\t') + 1;
		super_sub_len = sb.buf + sb.len - super_sub - 1;

		if (super_sub_len > cwd_len ||
		    strcmp(&cwd[cwd_len - super_sub_len], super_sub))
			die (_("BUG: returned path string doesn't match cwd?"));

		super_wt = xstrdup(cwd);
		super_wt[cwd_len - super_sub_len] = '\0';

		ret = real_path(super_wt);
		free(super_wt);
	}
	strbuf_release(&sb);

	code = finish_command(&cp);

	if (code == 128)
		/* '../' is not a git repository */
		return NULL;
	if (code == 0 && len == 0)
		/* There is an unrelated git repository at '../' */
		return NULL;
	if (code)
		die(_("ls-tree returned unexpected return code %d"), code);

	return ret;
}

int submodule_to_gitdir(struct strbuf *buf, const char *submodule)
{
	const struct submodule *sub;
	const char *git_dir;
	int ret = 0;

	strbuf_reset(buf);
	strbuf_addstr(buf, submodule);
	strbuf_complete(buf, '/');
	strbuf_addstr(buf, ".git");

	git_dir = read_gitfile(buf->buf);
	if (git_dir) {
		strbuf_reset(buf);
		strbuf_addstr(buf, git_dir);
	}
	if (!is_git_directory(buf->buf)) {
		gitmodules_config();
		sub = submodule_from_path(null_sha1, submodule);
		if (!sub) {
			ret = -1;
			goto cleanup;
		}
		strbuf_reset(buf);
		strbuf_git_path(buf, "%s/%s", "modules", sub->name);
	}

cleanup:
	return ret;
}
