int cmd_clean(int argc, const char **argv, const char *prefix)
{
	int i, res;
	int dry_run = 0, remove_directories = 0, quiet = 0, ignored = 0;
	int ignored_only = 0, config_set = 0, errors = 0, gone = 1;
	int rm_flags = REMOVE_DIR_KEEP_NESTED_GIT;
	struct strbuf abs_path = STRBUF_INIT;
	struct dir_struct dir;
	struct pathspec pathspec;
	struct strbuf buf = STRBUF_INIT;
	struct string_list exclude_list = STRING_LIST_INIT_NODUP;
	struct exclude_list *el;
	struct string_list_item *item;
	const char *qname;
	struct option options[] = {
		OPT__QUIET(&quiet, N_("do not print names of files removed")),
		OPT__DRY_RUN(&dry_run, N_("dry run")),
		OPT__FORCE(&force, N_("force")),
		OPT_BOOL('i', "interactive", &interactive, N_("interactive cleaning")),
		OPT_BOOL('d', NULL, &remove_directories,
				N_("remove whole directories")),
		{ OPTION_CALLBACK, 'e', "exclude", &exclude_list, N_("pattern"),
		  N_("add <pattern> to ignore rules"), PARSE_OPT_NONEG, exclude_cb },
		OPT_BOOL('x', NULL, &ignored, N_("remove ignored files, too")),
		OPT_BOOL('X', NULL, &ignored_only,
				N_("remove only ignored files")),
		OPT_END()
	};

	git_config(git_clean_config, NULL);
	if (force < 0)
		force = 0;
	else
		config_set = 1;

	argc = parse_options(argc, argv, prefix, options, builtin_clean_usage,
			     0);

	memset(&dir, 0, sizeof(dir));
	if (ignored_only)
		dir.flags |= DIR_SHOW_IGNORED;

	if (ignored && ignored_only)
		die(_("-x and -X cannot be used together"));

	if (!interactive && !dry_run && !force) {
		if (config_set)
			die(_("clean.requireForce set to true and neither -i, -n, nor -f given; "
				  "refusing to clean"));
		else
			die(_("clean.requireForce defaults to true and neither -i, -n, nor -f given;"
				  " refusing to clean"));
	}

	if (force > 1)
		rm_flags = 0;

	dir.flags |= DIR_SHOW_OTHER_DIRECTORIES;

	if (read_cache() < 0)
		die(_("index file corrupt"));

	if (!ignored)
		setup_standard_excludes(&dir);

	el = add_exclude_list(&dir, EXC_CMDL, "--exclude option");
	for (i = 0; i < exclude_list.nr; i++)
		add_exclude(exclude_list.items[i].string, "", 0, el, -(i+1));

	parse_pathspec(&pathspec, 0,
		       PATHSPEC_PREFER_CWD,
		       prefix, argv);

	fill_directory(&dir, &pathspec);

	for (i = 0; i < dir.nr; i++) {
		struct dir_entry *ent = dir.entries[i];
		int matches = 0;
		struct stat st;
		const char *rel;

		if (!cache_name_is_other(ent->name, ent->len))
			continue;

		if (pathspec.nr)
			matches = dir_path_match(ent, &pathspec, 0, NULL);

		if (pathspec.nr && !matches)
			continue;

		if (lstat(ent->name, &st))
			die_errno("Cannot lstat '%s'", ent->name);

		if (S_ISDIR(st.st_mode) && !remove_directories &&
		    matches != MATCHED_EXACTLY)
			continue;

		rel = relative_path(ent->name, prefix, &buf);
		string_list_append(&del_list, rel);
	}

	if (interactive && del_list.nr > 0)
		interactive_main_loop();

	for_each_string_list_item(item, &del_list) {
		struct stat st;

		if (prefix)
			strbuf_addstr(&abs_path, prefix);

		strbuf_addstr(&abs_path, item->string);

		/*
		 * we might have removed this as part of earlier
		 * recursive directory removal, so lstat() here could
		 * fail with ENOENT.
		 */
		if (lstat(abs_path.buf, &st))
			continue;

		if (S_ISDIR(st.st_mode)) {
			if (remove_dirs(&abs_path, prefix, rm_flags, dry_run, quiet, &gone))
				errors++;
			if (gone && !quiet) {
				qname = quote_path_relative(item->string, NULL, &buf);
				printf(dry_run ? _(msg_would_remove) : _(msg_remove), qname);
			}
		} else {
			res = dry_run ? 0 : unlink(abs_path.buf);
			if (res) {
				qname = quote_path_relative(item->string, NULL, &buf);
				warning(_(msg_warn_remove_failed), qname);
				errors++;
			} else if (!quiet) {
				qname = quote_path_relative(item->string, NULL, &buf);
				printf(dry_run ? _(msg_would_remove) : _(msg_remove), qname);
			}
		}
		strbuf_reset(&abs_path);
	}

	strbuf_release(&abs_path);
	strbuf_release(&buf);
	string_list_clear(&del_list, 0);
	string_list_clear(&exclude_list, 0);
	return (errors != 0);
}