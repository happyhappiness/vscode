static int handle_path_include(const char *path, struct config_include_data *inc)
{
	int ret = 0;
	struct strbuf buf = STRBUF_INIT;
	char *expanded;

	if (!path)
		return config_error_nonbool("include.path");

	expanded = expand_user_path(path, 0);
	if (!expanded)
		return error("could not expand include path '%s'", path);
	path = expanded;

	/*
	 * Use an absolute path as-is, but interpret relative paths
	 * based on the including config file.
	 */
	if (!is_absolute_path(path)) {
		char *slash;

		if (!cf || !cf->path)
			return error("relative config includes must come from files");

		slash = find_last_dir_sep(cf->path);
		if (slash)
			strbuf_add(&buf, cf->path, slash - cf->path + 1);
		strbuf_addstr(&buf, path);
		path = buf.buf;
	}

	if (!access_or_die(path, R_OK, 0)) {
		if (++inc->depth > MAX_INCLUDE_DEPTH)
			die(include_depth_advice, MAX_INCLUDE_DEPTH, path,
			    !cf ? "<unknown>" :
			    cf->name ? cf->name :
			    "the command line");
		ret = git_config_from_file(git_config_include, path, inc);
		inc->depth--;
	}
	strbuf_release(&buf);
	free(expanded);
	return ret;
}