static int include_by_gitdir(const struct config_options *opts,
			     const char *cond, size_t cond_len, int icase)
{
	struct strbuf text = STRBUF_INIT;
	struct strbuf pattern = STRBUF_INIT;
	int ret = 0, prefix;
	const char *git_dir;
	int already_tried_absolute = 0;

	if (opts->git_dir)
		git_dir = opts->git_dir;
	else
		goto done;

	strbuf_realpath(&text, git_dir, 1);
	strbuf_add(&pattern, cond, cond_len);
	prefix = prepare_include_condition_pattern(&pattern);

again:
	if (prefix < 0)
		goto done;

	if (prefix > 0) {
		/*
		 * perform literal matching on the prefix part so that
		 * any wildcard character in it can't create side effects.
		 */
		if (text.len < prefix)
			goto done;
		if (!icase && strncmp(pattern.buf, text.buf, prefix))
			goto done;
		if (icase && strncasecmp(pattern.buf, text.buf, prefix))
			goto done;
	}

	ret = !wildmatch(pattern.buf + prefix, text.buf + prefix,
			 icase ? WM_CASEFOLD : 0);

	if (!ret && !already_tried_absolute) {
		/*
		 * We've tried e.g. matching gitdir:~/work, but if
		 * ~/work is a symlink to /mnt/storage/work
		 * strbuf_realpath() will expand it, so the rule won't
		 * match. Let's match against a
		 * strbuf_add_absolute_path() version of the path,
		 * which'll do the right thing
		 */
		strbuf_reset(&text);
		strbuf_add_absolute_path(&text, git_dir);
		already_tried_absolute = 1;
		goto again;
	}
done:
	strbuf_release(&pattern);
	strbuf_release(&text);
	return ret;
}