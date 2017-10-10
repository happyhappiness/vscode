 		}
 		if (killed)
 			show_dir_entry(tag_killed, dir->entries[i]);
 	}
 }
 
-/*
- * Compile an argv_array with all of the options supported by --recurse_submodules
- */
-static void compile_submodule_options(const char **argv,
-				      const struct dir_struct *dir,
-				      int show_tag)
-{
-	if (line_terminator == '\0')
-		argv_array_push(&submodule_options, "-z");
-	if (show_tag)
-		argv_array_push(&submodule_options, "-t");
-	if (show_valid_bit)
-		argv_array_push(&submodule_options, "-v");
-	if (show_cached)
-		argv_array_push(&submodule_options, "--cached");
-	if (show_eol)
-		argv_array_push(&submodule_options, "--eol");
-	if (debug_mode)
-		argv_array_push(&submodule_options, "--debug");
-
-	/* Add Pathspecs */
-	argv_array_push(&submodule_options, "--");
-	for (; *argv; argv++)
-		argv_array_push(&submodule_options, *argv);
-}
+static void show_files(struct repository *repo, struct dir_struct *dir);
 
-/**
- * Recursively call ls-files on a submodule
- */
-static void show_gitlink(const struct cache_entry *ce)
+static void show_submodule(struct repository *superproject,
+			   struct dir_struct *dir, const char *path)
 {
-	struct child_process cp = CHILD_PROCESS_INIT;
-	int status;
-	char *dir;
-
-	prepare_submodule_repo_env(&cp.env_array);
-	argv_array_push(&cp.env_array, GIT_DIR_ENVIRONMENT);
-
-	if (prefix_len)
-		argv_array_pushf(&cp.env_array, "%s=%s",
-				 GIT_TOPLEVEL_PREFIX_ENVIRONMENT,
-				 prefix);
-	argv_array_pushf(&cp.args, "--super-prefix=%s%s/",
-			 super_prefix ? super_prefix : "",
-			 ce->name);
-	argv_array_push(&cp.args, "ls-files");
-	argv_array_push(&cp.args, "--recurse-submodules");
-
-	/* add supported options */
-	argv_array_pushv(&cp.args, submodule_options.argv);
-
-	cp.git_cmd = 1;
-	dir = mkpathdup("%s/%s", get_git_work_tree(), ce->name);
-	cp.dir = dir;
-	status = run_command(&cp);
-	free(dir);
-	if (status)
-		exit(status);
+	struct repository submodule;
+
+	if (repo_submodule_init(&submodule, superproject, path))
+		return;
+
+	if (repo_read_index(&submodule) < 0)
+		die("index file corrupt");
+
+	repo_read_gitmodules(&submodule);
+
+	show_files(&submodule, dir);
+
+	repo_clear(&submodule);
 }
 
-static void show_ce_entry(const char *tag, const struct cache_entry *ce)
+static void show_ce(struct repository *repo, struct dir_struct *dir,
+		    const struct cache_entry *ce, const char *fullname,
+		    const char *tag)
 {
-	struct strbuf name = STRBUF_INIT;
-	int len = max_prefix_len;
-	if (super_prefix)
-		strbuf_addstr(&name, super_prefix);
-	strbuf_addstr(&name, ce->name);
-
-	if (len >= ce_namelen(ce))
+	if (max_prefix_len > strlen(fullname))
 		die("git ls-files: internal error - cache entry not superset of prefix");
 
 	if (recurse_submodules && S_ISGITLINK(ce->ce_mode) &&
-	    submodule_path_match(&pathspec, name.buf, ps_matched)) {
-		show_gitlink(ce);
-	} else if (match_pathspec(&pathspec, name.buf, name.len,
-				  len, ps_matched,
+	    is_submodule_active(repo, ce->name)) {
+		show_submodule(repo, dir, ce->name);
+	} else if (match_pathspec(&pathspec, fullname, strlen(fullname),
+				  max_prefix_len, ps_matched,
 				  S_ISDIR(ce->ce_mode) ||
 				  S_ISGITLINK(ce->ce_mode))) {
-		if (tag && *tag && show_valid_bit &&
-		    (ce->ce_flags & CE_VALID)) {
-			static char alttag[4];
-			memcpy(alttag, tag, 3);
-			if (isalpha(tag[0]))
-				alttag[0] = tolower(tag[0]);
-			else if (tag[0] == '?')
-				alttag[0] = '!';
-			else {
-				alttag[0] = 'v';
-				alttag[1] = tag[0];
-				alttag[2] = ' ';
-				alttag[3] = 0;
-			}
-			tag = alttag;
-		}
+		tag = get_tag(ce, tag);
 
 		if (!show_stage) {
 			fputs(tag, stdout);
 		} else {
 			printf("%s%06o %s %d\t",
 			       tag,
 			       ce->ce_mode,
 			       find_unique_abbrev(ce->oid.hash, abbrev),
 			       ce_stage(ce));
 		}
-		write_eolinfo(ce, ce->name);
-		write_name(ce->name);
-		if (debug_mode) {
-			const struct stat_data *sd = &ce->ce_stat_data;
-
-			printf("  ctime: %d:%d\n", sd->sd_ctime.sec, sd->sd_ctime.nsec);
-			printf("  mtime: %d:%d\n", sd->sd_mtime.sec, sd->sd_mtime.nsec);
-			printf("  dev: %d\tino: %d\n", sd->sd_dev, sd->sd_ino);
-			printf("  uid: %d\tgid: %d\n", sd->sd_uid, sd->sd_gid);
-			printf("  size: %d\tflags: %x\n", sd->sd_size, ce->ce_flags);
-		}
+		write_eolinfo(repo->index, ce, fullname);
+		write_name(fullname);
+		print_debug(ce);
 	}
-
-	strbuf_release(&name);
 }
 
-static void show_ru_info(void)
+static void show_ru_info(const struct index_state *istate)
 {
 	struct string_list_item *item;
 
-	if (!the_index.resolve_undo)
+	if (!istate->resolve_undo)
 		return;
 
-	for_each_string_list_item(item, the_index.resolve_undo) {
+	for_each_string_list_item(item, istate->resolve_undo) {
 		const char *path = item->string;
 		struct resolve_undo_info *ui = item->util;
 		int i, len;
 
 		len = strlen(path);
 		if (len < max_prefix_len)
