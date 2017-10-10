 	}
 	strbuf_release(&buf);
 	free(expanded);
 	return ret;
 }
 
+static int prepare_include_condition_pattern(struct strbuf *pat)
+{
+	struct strbuf path = STRBUF_INIT;
+	char *expanded;
+	int prefix = 0;
+
+	expanded = expand_user_path(pat->buf, 1);
+	if (expanded) {
+		strbuf_reset(pat);
+		strbuf_addstr(pat, expanded);
+		free(expanded);
+	}
+
+	if (pat->buf[0] == '.' && is_dir_sep(pat->buf[1])) {
+		const char *slash;
+
+		if (!cf || !cf->path)
+			return error(_("relative config include "
+				       "conditionals must come from files"));
+
+		strbuf_realpath(&path, cf->path, 1);
+		slash = find_last_dir_sep(path.buf);
+		if (!slash)
+			die("BUG: how is this possible?");
+		strbuf_splice(pat, 0, 1, path.buf, slash - path.buf);
+		prefix = slash - path.buf + 1 /* slash */;
+	} else if (!is_absolute_path(pat->buf))
+		strbuf_insert(pat, 0, "**/", 3);
+
+	if (pat->len && is_dir_sep(pat->buf[pat->len - 1]))
+		strbuf_addstr(pat, "**");
+
+	strbuf_release(&path);
+	return prefix;
+}
+
+static int include_by_gitdir(const struct config_options *opts,
+			     const char *cond, size_t cond_len, int icase)
+{
+	struct strbuf text = STRBUF_INIT;
+	struct strbuf pattern = STRBUF_INIT;
+	int ret = 0, prefix;
+	const char *git_dir;
+
+	if (opts->git_dir)
+		git_dir = opts->git_dir;
+	else if (have_git_dir())
+		git_dir = get_git_dir();
+	else
+		goto done;
+
+	strbuf_realpath(&text, git_dir, 1);
+	strbuf_add(&pattern, cond, cond_len);
+	prefix = prepare_include_condition_pattern(&pattern);
+
+	if (prefix < 0)
+		goto done;
+
+	if (prefix > 0) {
+		/*
+		 * perform literal matching on the prefix part so that
+		 * any wildcard character in it can't create side effects.
+		 */
+		if (text.len < prefix)
+			goto done;
+		if (!icase && strncmp(pattern.buf, text.buf, prefix))
+			goto done;
+		if (icase && strncasecmp(pattern.buf, text.buf, prefix))
+			goto done;
+	}
+
+	ret = !wildmatch(pattern.buf + prefix, text.buf + prefix,
+			 icase ? WM_CASEFOLD : 0, NULL);
+
+done:
+	strbuf_release(&pattern);
+	strbuf_release(&text);
+	return ret;
+}
+
+static int include_condition_is_true(const struct config_options *opts,
+				     const char *cond, size_t cond_len)
+{
+
+	if (skip_prefix_mem(cond, cond_len, "gitdir:", &cond, &cond_len))
+		return include_by_gitdir(opts, cond, cond_len, 0);
+	else if (skip_prefix_mem(cond, cond_len, "gitdir/i:", &cond, &cond_len))
+		return include_by_gitdir(opts, cond, cond_len, 1);
+
+	/* unknown conditionals are always false */
+	return 0;
+}
+
 int git_config_include(const char *var, const char *value, void *data)
 {
 	struct config_include_data *inc = data;
+	const char *cond, *key;
+	int cond_len;
 	int ret;
 
 	/*
 	 * Pass along all values, including "include" directives; this makes it
 	 * possible to query information on the includes themselves.
 	 */
 	ret = inc->fn(var, value, inc->data);
 	if (ret < 0)
 		return ret;
 
 	if (!strcmp(var, "include.path"))
 		ret = handle_path_include(value, inc);
+
+	if (!parse_config_key(var, "includeif", &cond, &cond_len, &key) &&
+	    (cond && include_condition_is_true(inc->opts, cond, cond_len)) &&
+	    !strcmp(key, "path"))
+		ret = handle_path_include(value, inc);
+
 	return ret;
 }
 
 void git_config_push_parameter(const char *text)
 {
 	struct strbuf env = STRBUF_INIT;
