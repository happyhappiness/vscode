 		setenv(GIT_WORK_TREE_ENVIRONMENT, ".", 1);
 
 	set_git_dir(remove_leading_path(git_dir, work_tree));
 	initialized = 1;
 }
 
-static int check_repo_format(const char *var, const char *value, void *cb)
+static int check_repo_format(const char *var, const char *value, void *vdata)
 {
+	struct repository_format *data = vdata;
 	const char *ext;
 
 	if (strcmp(var, "core.repositoryformatversion") == 0)
-		repository_format_version = git_config_int(var, value);
-	else if (strcmp(var, "core.sharedrepository") == 0)
-		shared_repository = git_config_perm(var, value);
+		data->version = git_config_int(var, value);
 	else if (skip_prefix(var, "extensions.", &ext)) {
 		/*
 		 * record any known extensions here; otherwise,
 		 * we fall through to recording it as unknown, and
 		 * check_repository_format will complain
 		 */
 		if (!strcmp(ext, "noop"))
 			;
 		else if (!strcmp(ext, "preciousobjects"))
-			repository_format_precious_objects = git_config_bool(var, value);
+			data->precious_objects = git_config_bool(var, value);
 		else
-			string_list_append(&unknown_extensions, ext);
+			string_list_append(&data->unknown_extensions, ext);
+	} else if (strcmp(var, "core.bare") == 0) {
+		data->is_bare = git_config_bool(var, value);
+	} else if (strcmp(var, "core.worktree") == 0) {
+		if (!value)
+			return config_error_nonbool(var);
+		data->work_tree = xstrdup(value);
 	}
 	return 0;
 }
 
 static int check_repository_format_gently(const char *gitdir, int *nongit_ok)
 {
 	struct strbuf sb = STRBUF_INIT;
-	const char *repo_config;
-	config_fn_t fn;
-	int ret = 0;
-
-	string_list_clear(&unknown_extensions, 0);
+	struct strbuf err = STRBUF_INIT;
+	struct repository_format candidate;
+	int has_common;
 
-	if (get_common_dir(&sb, gitdir))
-		fn = check_repo_format;
-	else
-		fn = check_repository_format_version;
+	has_common = get_common_dir(&sb, gitdir);
 	strbuf_addstr(&sb, "/config");
-	repo_config = sb.buf;
+	read_repository_format(&candidate, sb.buf);
+	strbuf_release(&sb);
 
 	/*
-	 * git_config() can't be used here because it calls git_pathdup()
-	 * to get $GIT_CONFIG/config. That call will make setup_git_env()
-	 * set git_dir to ".git".
-	 *
-	 * We are in gitdir setup, no git dir has been found useable yet.
-	 * Use a gentler version of git_config() to check if this repo
-	 * is a good one.
+	 * For historical use of check_repository_format() in git-init,
+	 * we treat a missing config as a silent "ok", even when nongit_ok
+	 * is unset.
 	 */
-	git_config_early(fn, NULL, repo_config);
-	if (GIT_REPO_VERSION_READ < repository_format_version) {
-		if (!nongit_ok)
-			die ("Expected git repo version <= %d, found %d",
-			     GIT_REPO_VERSION_READ, repository_format_version);
-		warning("Expected git repo version <= %d, found %d",
-			GIT_REPO_VERSION_READ, repository_format_version);
-		warning("Please upgrade Git");
-		*nongit_ok = -1;
-		ret = -1;
+	if (candidate.version < 0)
+		return 0;
+
+	if (verify_repository_format(&candidate, &err) < 0) {
+		if (nongit_ok) {
+			warning("%s", err.buf);
+			strbuf_release(&err);
+			*nongit_ok = -1;
+			return -1;
+		}
+		die("%s", err.buf);
+	}
+
+	repository_format_precious_objects = candidate.precious_objects;
+	string_list_clear(&candidate.unknown_extensions, 0);
+	if (!has_common) {
+		if (candidate.is_bare != -1) {
+			is_bare_repository_cfg = candidate.is_bare;
+			if (is_bare_repository_cfg == 1)
+				inside_work_tree = -1;
+		}
+		if (candidate.work_tree) {
+			free(git_work_tree_cfg);
+			git_work_tree_cfg = candidate.work_tree;
+			inside_work_tree = -1;
+		}
+	} else {
+		free(candidate.work_tree);
 	}
 
-	if (repository_format_version >= 1 && unknown_extensions.nr) {
+	return 0;
+}
+
+int read_repository_format(struct repository_format *format, const char *path)
+{
+	memset(format, 0, sizeof(*format));
+	format->version = -1;
+	format->is_bare = -1;
+	string_list_init(&format->unknown_extensions, 1);
+	git_config_from_file(check_repo_format, path, format);
+	return format->version;
+}
+
+int verify_repository_format(const struct repository_format *format,
+			     struct strbuf *err)
+{
+	if (GIT_REPO_VERSION_READ < format->version) {
+		strbuf_addf(err, _("Expected git repo version <= %d, found %d"),
+			    GIT_REPO_VERSION_READ, format->version);
+		return -1;
+	}
+
+	if (format->version >= 1 && format->unknown_extensions.nr) {
 		int i;
 
-		if (!nongit_ok)
-			die("unknown repository extension: %s",
-			    unknown_extensions.items[0].string);
-
-		for (i = 0; i < unknown_extensions.nr; i++)
-			warning("unknown repository extension: %s",
-				unknown_extensions.items[i].string);
-		*nongit_ok = -1;
-		ret = -1;
+		strbuf_addstr(err, _("unknown repository extensions found:"));
+
+		for (i = 0; i < format->unknown_extensions.nr; i++)
+			strbuf_addf(err, "\n\t%s",
+				    format->unknown_extensions.items[i].string);
+		return -1;
 	}
 
-	strbuf_release(&sb);
-	return ret;
+	return 0;
 }
 
 /*
  * Try to read the location of the git directory from the .git file,
  * return path to git directory if found.
  *
